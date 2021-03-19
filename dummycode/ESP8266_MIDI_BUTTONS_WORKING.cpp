#include <MIDI.h>
// Create and bind the MIDI interface to the default hardware Serial port
MIDI_CREATE_DEFAULT_INSTANCE();

// set pin numbers
const int buttonPin1 = 14;     // Corresponds to D5
const int buttonPin2 = 12;     // Corresponds to D6
const int buttonPin3 = 13;     // Corresponds to D7

// variable for storing the pushbutton status
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;

void setup(){

  MIDI.begin();  // Listen to all incoming messages
  // initialize the pushbutton pin as an input
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);

  // Serial.begin(115200);
}

void printMessage(String button, String status){
  Serial.print(button);
  Serial.println(status);
}

void loop() {
  // read the state of the pushbutton value
  if(buttonState1 != digitalRead(buttonPin1)){
    buttonState1 = digitalRead(buttonPin1);
    if(buttonState1 == HIGH){
      // printMessage("Button1 ", "Pressed");
      MIDI.sendProgramChange(1, 1);
      delay(250);
    }else{
      // what to do when not pressed
    }
  }

  if(buttonState2 != digitalRead(buttonPin2)){
    buttonState2 = digitalRead(buttonPin2);
    if(buttonState2 == HIGH){
      // printMessage("Button2 ", "Pressed");
      MIDI.sendProgramChange(2, 1);
      delay(250);
    }else{
      // what to do when not pressed
    }
  }

  if(buttonState3 != digitalRead(buttonPin3)){
    buttonState3 = digitalRead(buttonPin3);
    if(buttonState3 == HIGH){
      // printMessage("Button3 ", "Pressed");
      MIDI.sendProgramChange(3, 1);
      delay(250);
    }else{
      // what to do when not pressed
    }
  }

}