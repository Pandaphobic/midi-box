#include <Arduino.h>
#include "LittleFS.h"
#include "ArduinoJson.h"
#include "iostream"

int currentTime;
int duration;
int startTime;
bool timerOn = false;

#include "Midi_Controller.h" // My Midi Controller
#include "Preset_Controller.h" // My Preset Controller
#include "OLED_Controller.h" // My OLED controller
#include "Input_Controller.h" // My Input Controller

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  if(LoadPresets()){
    Serial.println("Presets loaded to memory");
  } else {
    Serial.println("Could not load presets");
  }
  initButtons();
}

void screenTimer(){
  if(timerOn){
    currentTime = millis();
  
    if(currentTime - startTime >= duration){
      display.clearDisplay();
      timerOn = false;
    };
  }
}

void loop() {

  handleButtonPress();
  screenTimer();

}
