#include <Arduino.h>
#include "LittleFS.h"
#include "ArduinoJson.h"
#include "iostream"

#include "Midi_Controller.h" // My Midi Controller
#include "Preset_Controller.h" // My Preset Controller
#include "OLED_Controller.h" // My OLED controller
#include "Input_Controller.h" // My Input Controller

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  if(LoadPresets()){
    Serial.print("Presets loaded to memory");
  } else {
    Serial.print("Could not load presets");
  }
}



void loop() {
  // put your main code here, to run repeatedly:

}