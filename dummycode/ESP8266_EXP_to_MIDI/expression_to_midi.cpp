#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Arduino.h>
#include "LittleFS.h"
#include <MIDI.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0

int sensorValue = 0;         // value read from the pot
int midiOutput = 0;          // Midi output is 0-127 
float maxIn = 890.0;         // Maximum value from expression pedal
float multiplier = 0.00;     // initialize multiplier


void setup() {
  // initialize serial communication at 115200
  Serial.begin(115200);
  multiplier += 127.0 / maxIn; // Makes it so min is 0 and max is 127
}

void loop() {
  // read the analog in value
  sensorValue = analogRead(analogInPin);
  
  midiOutput = (int)(sensorValue * multiplier);
 
  // print the readings in the Serial Monitor
  Serial.print("sensor = ");
  Serial.println(midiOutput);
  
  delay(250);
}