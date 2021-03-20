/* ----- Section Overview -----

This section is primarily to handle inputs from PCF8574 chips on the main board.
The aim is that this be used as the primary controller. Trigger events from here,
catch inputs, handle interupts - anything that connects human interaction to code
must come through here.

*/
#include "PCF8574.h" 
#include "Wire.h"

// Buttons and Interrupts
#define ESP8266_INTERRUPTED_PIN 12  // D6 on the board
PCF8574 pcf8574_1(0x38);
PCF8574 pcf8574_2(0x39);            // Set i2c address
bool keyPressed = false;

void ICACHE_RAM_ATTR handleInterrupt(){
  keyPressed = true;
};

void handleButtonPress(){

  if(keyPressed){
    PCF8574::DigitalInput val_1 = pcf8574_1.digitalReadAll();
    PCF8574::DigitalInput val_2 = pcf8574_2.digitalReadAll();

    if(val_1.p0 == LOW) preset[0].Send();
    if(val_1.p1 == LOW) preset[1].Send();
    if(val_1.p2 == LOW) preset[2].Send();
    if(val_1.p3 == LOW) preset[3].Send();
    if(val_1.p4 == LOW) preset[4].Send();
    if(val_1.p5 == LOW) preset[5].Send();
    if(val_1.p6 == LOW) preset[6].Send();
    if(val_1.p7 == LOW) preset[7].Send();

    if(val_2.p0 == LOW) preset[8].Send();
    if(val_2.p1 == LOW) preset[9].Send();
    if(val_2.p2 == LOW) preset[10].Send();
    if(val_2.p3 == LOW) preset[11].Send();
    if(val_2.p4 == LOW) preset[12].Send();
    if(val_2.p5 == LOW) preset[13].Send();
    if(val_2.p6 == LOW) preset[14].Send();
    if(val_2.p7 == LOW) preset[15].Send();
    

    // if (val_1.1==LOW) preset[0].SendPC());
    
    keyPressed= false;
  }
};

void initButtons(){

  pinMode(ESP8266_INTERRUPTED_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ESP8266_INTERRUPTED_PIN), handleInterrupt, FALLING);

  Serial.print("Init buttons 1-8 (pcf8574_1)...");
  if (pcf8574_1.begin()){
    for(int i = 0; i >= 7; i++ ){
      if(i < 8){
        pcf8574_1.pinMode(i, INPUT);
      }
    };
    Serial.println("OK");
  } else {
    Serial.println("KO");
  }

  Serial.print("Init buttons 9-16 (pcf8574_2)...");
  if (pcf8574_2.begin()){
    for(int i = 8; i >= 15; i++ ){
      if(i < 8){
        pcf8574_2.pinMode(i, INPUT);
      }
    };
    Serial.println("OK");
  } else {
    Serial.println("KO");
  }  
};