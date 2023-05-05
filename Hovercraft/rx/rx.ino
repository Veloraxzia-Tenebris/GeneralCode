#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 ant(7, 8); //CE, CSN

const byte address[6] = "000001";

int leftStickPin = A2;
int rightStickPin = A1;
int potPin = A0;

int leftStick = 0;
int rightStick = 0;
int pot = 0;

Adafruit_SSD1306 disp(128, 64, &Wire, -1);
// Screen address: 0x3D

void setup() {
  Serial.begin(9600);
  ant.begin();
  ant.openWritingPipe(address);
  ant.setPALevel(RF24_PA_MIN);
  ant.stopListening();

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
    Serial.println("Screen not working");
    for(;;);
  }
  disp.clearDisplay();
  disp.setTextSize(3);
  disp.setTextColor(WHITE);
  disp.setCursor(64, 10);
  disp.println("Display On");
  disp.display();
  delay(2000);
  disp.clearDisplay();
  testscrolltext();
}

void loop() {
  leftStick = analogRead(leftStickPin);
  rightStick = analogRead(rightStickPin);
  pot = analogRead(potPin);

  disp.clearDisplay();
  disp.setTextSize(1);
  disp.setTextColor(WHITE);
  disp.setCursor(0, 10);
  disp.println("Left: %d", leftStick);
  disp.setTextColor(BLACK);
  disp.setCursor(60, 10);
  disp.println("Right: %d", rightStick);
  disp.display();
}
