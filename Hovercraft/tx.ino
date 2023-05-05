#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdlib.h>

RF24 ant(7, 8); //CE, CSN

const byte address[6] = "00001";

int leftStickPin = A2;
int rightStickPin = A1;
int potPin = A0;

int leftStick = 0;
int rightStick = 0;
int pot = 0;

Adafruit_SSD1306 disp(128, 64, &Wire, -1);

void setup() {
	Serial.begin(9600);
	ant.begin();
	ant.openWritingPipe(address);
	ant.setPALevel(RF24_PA_MIN);
	ant.stopListening();

	if(!disp.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
		Serial.println("Screen not working");
		for(;;);
	}
	disp.clearDisplay();
	delay(500);
	disp.setTextSize(2);
	disp.setTextColor(WHITE);
	disp.setCursor(32, 0);
	disp.println("Display");
	disp.setCursor(50, 16);
	disp.println("On");
	disp.display();
	delay(2000);
	disp.clearDisplay();
}

void loop() {
	leftStick = analogRead(leftStickPin);
	rightStick = analogRead(rightStickPin);
	pot = analogRead(potPin);

	disp.clearDisplay();
	disp.setTextSize(1);
	disp.setTextColor(WHITE);
	disp.setCursor(0, 20);
	disp.println("Left: ");
	disp.setCursor(40, 20);
	disp.println(leftStick);
	disp.setCursor(0, 40);
	disp.println("Right: ");
	disp.setCursor(40, 40);
	disp.println(rightStick);
	disp.setCursor(70, 20);
	disp.println("Dial: ");
	disp.setCursor(100, 20);
	disp.println(pot);
	disp.display();

	leftStick += 1000;
	rightStick += 1000;
	pot += 1000;

	char antOut[8] = "";
	char antOutS[4] = "";
	itoa(leftStick, antOut, 4);
	itoa(rightStick, antOutS, 4);
	strncat(antOut, antOutS, 4);
	ant.write(&antOut, 12);
	delay(10);
}