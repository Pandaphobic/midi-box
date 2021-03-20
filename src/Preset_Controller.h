/* ----- Section Overview -----

This sections should only be used when interacting with preset files driectly
through Little FS. Think file writes / updates and things like that. We also
initiate the presets into flash memory to make the midi message array from it.

*/

MidiPreset preset[16];

void presetsLoaded(){
  for(int i = 0; i < 16; i++){
      if(preset[i].getType() != "null"){
        Serial.print("Title: ");
        Serial.println(preset[i].getTitle());
        Serial.print("Type: ");
        Serial.println(preset[i].getType());
        Serial.print("Value: ");
        Serial.println(preset[i].getValue());
        Serial.print("Channel: ");
        Serial.println(preset[i].getChannel());
        Serial.print("Velocity: ");
        Serial.println(preset[i].getVelocity());
      } else {
        Serial.print(preset[i].getTitle());
        Serial.println(": Missing Type");
      }
    }
};

bool LoadPresets(){
  // if presets exist, return true
  DynamicJsonDocument doc(1024);
  LittleFS.begin();
  File f = LittleFS.open("/PRESET_LIST.json", "r");
  if(!f){
    Serial.println("Failed to open midi preset file");
    return false;
  } else {
    String s = f.readString();
    deserializeJson(doc, s);
    JsonObject obj = doc.as<JsonObject>();

    for(int i = 0; i < 16; i++){
      // All this to look for 8 buttons in the JSON Preset File
      char index_string[32];              // Reserve space (should be brought down)
      int index = i + 1;                  // index 0 offset
      sprintf(index_string, "%d", index); 
      char selector[64] = "button_";

      String title[16];
      title[i] = strcat(selector, index_string);     // concat to button_i
      
      preset[i].setTitle(title[i]);
      preset[i].setType(obj[title[i]]["type"].as<String>());
      preset[i].setValue(obj[title[i]]["value"].as<int>());
      preset[i].setChannel(obj[title[i]]["channel"].as<int>());
      preset[i].setVelocity(obj[title[i]]["velocity"].as<int>());
    };
    presetsLoaded();
    return true;
    
    
    // Function that applies presets to current presets in memory

  }
  LittleFS.end();
};

