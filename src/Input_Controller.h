/* ----- Section Overview -----

This section is primarily to handle inputs from PCF8574 chips on the main board.
The aim is that this be used as the primary controller. Trigger events from here,
catch inputs, handle interupts - anything that connects human interaction to code
must come through here.

*/

/*
 * PCF8574 GPIO Port Expand
 *
 * PCF8574    ----- 0x38
 * A0         ----- GRD (VCC would make this 0x39)
 * A1         ----- GRD
 * A2         ----- GRD
 * VSS        ----- GRD
 * VDD        ----- 5V/3.3V
 * SDA        ----- GPIO_4  -- D2 (ESP8266)
 * SCL        ----- GPIO_5  -- D1 (ESP8266)
 * INT        ----- GPIO_14 -- D6 (ESP8266)
 *
 * P0     ----------------- BUTTON0
 * P1     ----------------- BUTTON1
 * P2     ----------------- BUTTON2
 * P3     ----------------- BUTTON3
 * P4     ----------------- BUTTON4
 * P5     ----------------- BUTTON5
 * P6     ----------------- BUTTON6
 * P7     ----------------- BUTTON7
 *
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

    // Haven't found a way to shorten this *yet*
    // if(val_1.p0 == LOW) Serial.println("1");
    // if(val_1.p1 == LOW) Serial.println("2");
    // if(val_1.p2 == LOW) Serial.println("3");
    // if(val_1.p3 == LOW) Serial.println("4");
    // if(val_1.p4 == LOW) Serial.println("5");
    // if(val_1.p5 == LOW) Serial.println("6");
    // if(val_1.p6 == LOW) Serial.println("7");
    // if(val_1.p7 == LOW) Serial.println("8");

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
  pcf8574_1.pinMode(0, INPUT);
  pcf8574_1.pinMode(1, INPUT);
  pcf8574_1.pinMode(2, INPUT);
  pcf8574_1.pinMode(3, INPUT);
  pcf8574_1.pinMode(4, INPUT);
  pcf8574_1.pinMode(5, INPUT);
  pcf8574_1.pinMode(6, INPUT);
  pcf8574_1.pinMode(7, INPUT);
  
  Serial.print("Init buttons (pcf8574_1)...");
  if (pcf8574_1.begin()){
    Serial.println("OK");
  } else {
    Serial.println("KO");
  }

  pcf8574_2.pinMode(0, INPUT);
  pcf8574_2.pinMode(1, INPUT);
  pcf8574_2.pinMode(2, INPUT);
  pcf8574_2.pinMode(3, INPUT);
  pcf8574_2.pinMode(4, INPUT);
  pcf8574_2.pinMode(5, INPUT);
  pcf8574_2.pinMode(6, INPUT);
  pcf8574_2.pinMode(7, INPUT);

  Serial.print("Init buttons (pcf8574_2)...");
  if (pcf8574_2.begin()){
    Serial.println("OK");
  } else {
    Serial.println("KO");
  }
};

// void initButtons(){

//   pinMode(ESP8266_INTERRUPTED_PIN, INPUT_PULLUP);
//   attachInterrupt(digitalPinToInterrupt(ESP8266_INTERRUPTED_PIN), handleInterrupt, FALLING);

//   Serial.print("Init buttons 1-8 (pcf8574_1)...");
//   if (pcf8574_1.begin()){
//     // for(int i = 0; i >= 7; i++ ){
//     //   if(i < 8){
//     //     pcf8574_1.pinMode(i, INPUT);
//     //   }
//     // };
//     Serial.println("OK");
//   } else {
//     Serial.println("KO");
//   }

//   Serial.print("Init buttons 9-16 (pcf8574_2)...");
//   if (pcf8574_2.begin()){
//     for(int i = 8; i >= 15; i++ ){
//       if(i < 8){
//         pcf8574_2.pinMode(i, INPUT);
//       }
//     };
//     Serial.println("OK");
//   } else {
//     Serial.println("KO");
//   }  
// };