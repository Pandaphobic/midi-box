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

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET LED_BUILTIN    // Reset pin #
#define SCREEN_ADDRESS 0x3C       // 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* Set these to your desired credentials. */
#define APSSID "MidHeavy"
#define APPSK  "thereisnospoon"
const char *ssid = APSSID;
const char *password = APPSK;
ESP8266WebServer server(80);

// Create and bind the MIDI interface to the default hardware Serial port
MIDI_CREATE_DEFAULT_INSTANCE();
// set pin numbers
const int buttonPin1 = 14;     // Corresponds to D5
const int buttonPin2 = 12;     // Corresponds to D6
const int buttonPin3 = 13;     // Corresponds to D7

// Buttons Setup (initial state)
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;

// Expession Pedal Setup
const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0
float sensorValue = 0;       // value read from the pot
int midiOutput = 0;          // Midi output is 0-127 
double maxIn = 910.0;        // Maximum value from expression pedal
double multiplier = 127.0 / maxIn;

// What happens when someone visist 192.168.4.1/
void handleRoot() {
  LittleFS.begin();
  File f = LittleFS.open("/index.html", "r");
  if(!f){
    Serial.println("Failed to open index.htm");
  }
  else{
    String s = f.readString();
    server.send(200, "text/html", s);
  }
  LittleFS.end();
}

void drawNetworkInfo(IPAddress myIP) {
  /* This section displays the network relevant details
  to enable the user to connect to the settings page  */
  
  // Display init and setup     
  display.clearDisplay(); 
  display.display();  
  // Font and starting position setup
  display.setTextSize(1);
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.setCursor(0,0);
  // Display Title Text         
  display.println(F(" Network Info"));

  // Font change (no more background)
  display.setTextColor(SSD1306_WHITE, SSD1306_WHITE);
  // Display Network details
  display.print(F("SSID: ")); display.println(ssid);
  display.print(F("PASS: ")); display.println(password);
  display.print(F("URL: ")); display.println(myIP);
  display.display();
  delay(2000);
}

String longtype = "";

void drawMidiMessage(String type, int data, int channel){
  longtype = "";

  if(type == "PC"){
    longtype = "Program Change";
  }else if(type == "CC"){
    longtype = "Control Change";
  }else if(type == "SE"){
    longtype = "System Exclusive";
  }else {
    longtype = "Custom Data";
  }

  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(longtype);
  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.print(data); 
  display.print(","); 
  display.print(channel);
  display.display();
}

void setup() {
  delay(1000);
  Serial.begin(115200);

  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();        // seems out of place but this is what draws the splash screen
  delay(1500);
  drawNetworkInfo(myIP);    // Draw 'stylized' characters
  Serial.end();             // If left on, messes with Midi
  
  // Fire up a midi instance (default channel 1 if left blank)
  MIDI.begin(); 
  // initialize the pushbutton pin as an input
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
}

void handleExpression(){
  // read the analog in value
  if(analogRead(analogInPin)- sensorValue > 3
      || sensorValue - analogRead(analogInPin) > 3){
      sensorValue = analogRead(analogInPin);
      midiOutput = (int)(sensorValue * multiplier);
      MIDI.sendControlChange(11, midiOutput, 2);
      drawMidiMessage("CC", midiOutput, 2);
      }
}

void handleButtons(){
 // read the state of the pushbutton value
  if(buttonState1 != digitalRead(buttonPin1)){
    buttonState1 = digitalRead(buttonPin1);
    if(buttonState1 == HIGH){
      
      String type = "PC";
      int data = 1;
      int channel = 1;

      MIDI.sendProgramChange(data, channel);
      drawMidiMessage(type, data, channel);
      delay(50);
    }
  }

  if(buttonState2 != digitalRead(buttonPin2)){
    buttonState2 = digitalRead(buttonPin2);
    if(buttonState2 == HIGH){

      String type = "PC";
      int data = 2;
      int channel = 1;

      MIDI.sendProgramChange(data, channel);
      drawMidiMessage(type, data, channel);
      delay(50);
    }
  }

  if(buttonState3 != digitalRead(buttonPin3)){
    buttonState3 = digitalRead(buttonPin3);
    if(buttonState3 == HIGH){

      String type = "PC";
      int data = 3;
      int channel = 1;

      MIDI.sendProgramChange(data, channel);
      drawMidiMessage(type, data, channel);
      delay(50);
    }
  }
}

void loop() {
  server.handleClient();
  // Watch midi inputs for changes
  handleButtons();
  handleExpression();
  
}

