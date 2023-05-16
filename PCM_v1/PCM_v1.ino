/*
	Code for the Powertrain Control Module (PCM) of LMS23
	by Sonny Ji, based on, idk, stuff and thangs
	Any library included in this gets credit, yada yada, some legal stuff
	Idk how to code, plz don't be mean to me :pleading:
*/

#include <ACAN_T4.h>
#include <Arduino.h>

// Definitions because words mean things and numbers are ???
// Communication stuff
#define CAN_TX			22
#define CAN_RX			23
// APPS
#define APPS_1			14
#define APPS_1_PWR		15
#define APPS_1_GND		16
#define APPS_2			17
#define APPS_2_PWR		18
#define APPS_2_GND		19
// Outputs to MC
#define REGEN_DISABLE	10
#define FORWARD_ENABLE	8
#define START			7
#define IGN			6
// Outputs to big relay bois
#define ACC_FAN		25
#define RAD_FAN		12
#define SDC			11
// Inputs from dash
#define REGEN_SW		36
#define PUMP_SW		37
#define START_BTN		26
#define IGN_SW			5
#define DRIVE_READY_SW	4
#define ACC_FAN_SW		3
#define RAD_FAN_SW		2
// Other important car stuff inputs
#define BRAKE_F		21
#define RAD_THERM		41
// Other important car stuff outputs
#define BRAKE_LIGHT		20
#define SOUND			24

// Thermistor stuff
#define REFERENCE_RESISTOR 10000
#define THERMISTOR_BETA 8

// States for inputs from dash
int regenSW = 0;
int pumpSW = 0;
int startBTN = 0;
int ignSW = 0;
int driveReadySW = 0;
int accFanSW = 0;
int radFanSW = 0;
// Values for analog inputs
int apps1 = 0;
int apps1pwr = 0;
int apps1gnd = 0;
int apps2 = 0;
int apps2pwr = 0;
int apps2gnd = 0;
int brake = 0;
int radTherm = 0;



// Converted APPS values
int accelerator1 = 0;
int accelerator2 = 0;
int acceleratorBoth = 0;
int torque = 0;
// Convert brake value
int brakes = 0;
// Convert temperature value
float radTempRaw = 0; // Radiator thermistor resistance value
float radTemp = 0;
// Other internal counters and stuff
int startBTNPressTimeCounter = 0;
int delayTime = 10;
// CAN variables
CANMessage msg;



void setup() {
	// Setup serial for debug messages
	Serial.begin(115200);
	// Digital input pins (Switches and buttons from dash)
	pinMode(REGEN_SW, INPUT);
	pinMode(PUMP_SW, INPUT);
	pinMode(START_BTN, INPUT);
	pinMode(IGN_SW, INPUT);
	pinMode(DRIVE_READY_SW, INPUT);
	pinMode(ACC_FAN_SW, INPUT);
	pinMode(RAD_FAN_SW, INPUT);
	// Digital output pins for MC
	pinMode(REGEN_DISABLE, OUTPUT);
	pinMode(FORWARD_ENABLE, OUTPUT);
	pinMode(START, OUTPUT);
	pinMode(IGN, OUTPUT);
	// Pins for other car stuff
	pinMode(BRAKE_LIGHT, OUTPUT);
	pinMode(SDC, OUTPUT);
	// CAN stuff
	delay(400);
	ACAN_T4_Settings settings (500 * 1000); // 500 kbit/s
	settings.mLoopBackMode = false;
	settings.mSelfReceptionMode = false;
	const uint32_t errorCode = ACAN_T4::can3.begin(settings);
	if(0 == errorCode) {
		Serial.println("CAN3: OK");
	} else {
		Serial.print("Error can3: 0x");
		Serial.println(errorCode, HEX);
	}
	msg.id = 0x0C0;
	msg.buf[0] = 0; // Torque command
	msg.buf[1] = 0; // Torque command
	msg.buf[2] = 0; // Speed command
	msg.buf[3] = 0; // Speed command
	msg.buf[4] = 1; // Direction command
	msg.buf[5] = 1; // [0] Inverter enable, [1] Inverter discharge, [2] Speed mode enable
	msg.buf[6] = 0; // Commanded torque limit
	msg.buf[7] = 0; // Commanded torque limit
	// See page 31 of the CAN protocol documentation
}

void loop() {
	// Read all dash buttons and switches
	readDashInputs();
	// Read all analog inputs (APPS / Brakes / Thermistor)
	readAnalogInputs();
	// Convert analog values from raw to good
	convertAnalogInputs();
	// Write all the motor controller signals
	writeMCOutputs();
	// Write CAN torque message to motor controller
	CANTorqueCommand();
	// Loop delay
	delay(delayTime);
}

// Function to read all dash buttons and switches
void readDashInputs() {
	// Regen switch state stuff
	if(digitalRead(REGEN_SW) == HIGH) {
		if(regenSW == 0) {
			Serial.println("REGEN_SW Enabled");
		}
		regenSW = 1;
	} else if(digitalRead(REGEN_SW) == LOW) {
		if(regenSW == 1) {
			Serial.println("REGEN_SW Disabled");
		}
		regenSW = 0;
	}
	// Pump switch state stuff
	if(digitalRead(PUMP_SW) == HIGH) {
		if(pumpSW == 0) {
			Serial.println("PUMP_SW Enabled");
		}
		pumpSW = 1;
	} else if(digitalRead(PUMP_SW) == LOW) {
		if(pumpSW == 1) {
			Serial.println("PUMP_SW Disabled");
		}
		pumpSW = 0;
	}
	// Start button state stuff
	if(digitalRead(START_BTN) == HIGH) {
		if(startBTN == 0) {
			Serial.println("START_BTN Enabled");
		}
		startBTN = 1;
	} else if(digitalRead(START_BTN) == LOW) {
		if(startBTN == 1) {
			Serial.println("START_BTN Disabled");
		}
		startBTN = 0;
	}
	// Ignition switch state stuff
	if(digitalRead(IGN_SW) == HIGH) {
		if(ignSW == 0) {
			Serial.println("IGN_SW Enabled");
		}
		ignSW = 1;
	} else if(digitalRead(IGN_SW) == LOW) {
		if(ignSW == 1) {
			Serial.println("IGN_SW Disabled");
		}
		ignSW = 0;
	}
	// Drive-ready switch state stuff
	if(digitalRead(DRIVE_READY_SW) == HIGH) {
		if(driveReadySW == 0) {
			Serial.println("DRIVE_READY_SW Enabled");
		}
		driveReadySW = 1;
	} else if(digitalRead(DRIVE_READY_SW) == LOW) {
		if(driveReadySW == 1) {
			Serial.println("DRIVE_READY_SW Disabled")
		}
		driveReadySW = 0;
	}
	// Accumulator fan switch state stuff
	if(digitalRead(ACC_FAN_SW) == HIGH) {
		if(accFanSW == 0) {
			Serial.println("ACC_FAN_SW Enabled");
		}
		accFanSW = 1;
	} else if(digitalRead(ACC_FAN_SW) == LOW) {
		if(accFanSW == 1) {
			Serial.println("ACC_FAN_SW Disabled")
		}
		accFanSW = 0;
	}
    // Radiator fan switch state stuff
	if(digitalRead(RAD_FAN_SW) == HIGH) {
		if(radFanSW == 0) {
			Serial.println("RAD_FAN_SW Enabled");
		}
		radFanSW = 1;
	} else if(digitalRead(RAD_FAN_SW) == LOW) {
		if(radFanSW == 1) {
			Serial.println("RAD_FAN_SW Disabled");
		}
		radFanSW = 0;
	}
}

// Function to read all analog inputs (APPS / Brakes / Thermistor)
void readAnalogInputs() {
	// APPS 1 stuff
	apps1 = analogRead(APPS_1);
	Serial.print("APPS_1 is ");
	Serial.println(apps1);
	apps1pwr = analogRead(APPS_1_PWR);
	Serial.print("APPS_1_PWR is ");
	Serial.println(apps1pwr);
	apps1gnd = analogRead(APPS_1_GND);
	Serial.print("APPS_1_GND is ");
	Serial.println(apps1gnd);
	// APPS 2 stuff
	apps2 = analogRead(APPS_2);
	Serial.print("APPS_2 is ");
	Serial.println(apps2);
	apps2pwr = analogRead(APPS_2_PWR);
	Serial.print("APPS_2_PWR is ");
	Serial.println(apps2pwr);
	apps2gnd = analogRead(APPS_2_GND);
	Serial.print("APPS_2_GND is ");
	Serial.println(apps2gnd);
	// Brake stuff
	brake = analogRead(BRAKE_F);
	Serial.print("BRAKE_F is ");
	Serial.println(brake);
	// Thermistor stuff
	radTherm = analogRead(RAD_THERM);
	Serial.print("RAD_THERM is ");
	Serial.println(radTherm);
}

// Function to write all the motor controller signals
void writeMCOutputs() {
	// Disable regenerative braking
	if(regenSW == 1) {
		digitalWrite(REGEN_DISABLE, HIGH);
	} else {
		digitalWrite(REGEN_DISABLE, LOW);
	}
	// Enable forward motion
	if(driveReadySW == 1) {
		digitalWrite(FORWARD_ENABLE, HIGH);
	} else {
		digitalWrite(FORWARD_ENABLE, LOW);
	}
	// Enable ignition
	if(ignSW == 1) {
		digitalWrite(IGN, HIGH);
	} else {
		digitalWrite(IGN, LOW);
	}
	// Enable start
	if(startBTN == 1) {
		startBTNPressTimeCounter += delayTime;
		if(startBTNPressTimeCounter >= (delayTime * 30)) {
			digitalWrite(START, HIGH);
		} else {
			digitalWrite(START, LOW);
		}
	}
}

// Function to convert analog values from raw to good
void convertAnalogInputs() {
	// APPS stuff
	accelerator1 = map(apps1, apps1gnd, apps1pwr, 0, 511);
	accelerator2 = map(apps2, apps2gnd, apps2pwr, 0, 511);
	if(((accelerator1 - accelerator2) <= 50) || ((accelerator2 - accelerator1) <= 50)) {
		acceleratorBoth = (int) (accelerator1 + accelerator2) >> 1;
	}
	// Brake stuff
	brakes = map(brake, 0, 1023, 0, 511);
	// Thermistor stuff
	radTempRaw = REFERENCE_RESISTOR / (1023 / (radTherm - 1));
	// (1 / ((log(Thermistor resistance / Nominal thermistor resistance) / Thermistor beta) + (1 / (Nominal thermistor temperature + 273.15)))) - 273.15
	radTemp = (1 / ((log(radTempRaw / 10000) / THERMISTOR_BETA) + (1 / 298.15))) - 273.15;
}

// Function to do all the other stuff in the car
void otherCarStuff() {
	// Brake stuff
	if(brakes >= 25) {
		digitalWrite(BRAKE_LIGHT, HIGH);
	} else {
		digitalWrite(BRAKE_LIGHT, LOW);
	}
	// Sound device stuff
	tone(SOUND, 784, 4000);
	// SDC stuff
	digitalWrite(SDC, HIGH);
	// Cooling stuff
	if(radTemp > 40) {
		digitalWrite(ACC_FAN, HIGH);
		digitalWrite(RAD_FAN, HIGH);
	} else {
		if(accFanSW == 1) {
			digitalWrite(ACC_FAN, HIGH);
		} else {
			digitalWrite(ACC_FAN, LOW);
		}
		if(radFanSW == 1) {
			digitalWrite(RAD_FAN, HIGH);
		} else {
			digitalWrite(RAD_FAN, LOW);
		}
	}
}

// Function to set CAN message to motor controller
void CANTorqueCommand() {
	msg.id = 0x0C0;
	// Max torque is (Parallel cells = 7) * (Peak discharge current = 35) * (Kt = 0.61) = 149.45 Nm
	torque = map(acceleratorBoth, 0, 511, 0, 1494)
	// Total torque = ((x + (y * 256)) / 10) Nm
	msg.buf[0] = torque & 0b11111111; // Torque command => x, first 8 bits
	msg.buf[1] = (torque >> 8) & 0b11111111; // Torque command => y, second 8 bits
	msg.buf[2] = 0; // Speed command => Off
	msg.buf[3] = 0; // Speed command => Off
	msg.buf[4] = 1; // Direction command => Forwards
	msg.buf[5] = 1; // Inverter enable => On
	msg.buf[6] = 0; // Commanded torque limit => Default to EEPROM
	msg.buf[7] = 0; // Commanded torque limit => Default to EEPROM
	// Send message
	ACAN_T4::can3.tryToSend(msg);
}