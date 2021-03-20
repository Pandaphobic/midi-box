#include "MIDI.h"

// Create and bind the MIDI interface to the default hardware Serial port
MIDI_CREATE_DEFAULT_INSTANCE();

class MidiPreset {
private:
  String Title;
  String Type;
  int Value;
  int Velocity;
  int Channel;

public:
  MidiPreset(String title, String type, int value, int velocity, int channel){
    Title = title;
    Type = type;
    Value = value;
    Velocity = velocity;
    Channel = channel;
  }

  MidiPreset(){
    Type = "NA";
    Value = 0;
    Velocity = 0;
    Channel = 0;
  }

  // GETTERS
  String getTitle(){return Title;}
  String getType(){return Type;}
  int getValue(){return Value;}
  int getVelocity(){return Velocity;}
  int getChannel(){return Channel;}

  // SETTERS
  void setTitle(String title){Title = title;}  
  void setType(String type){Type = type;}  
  void setValue(int value){Value = value;} 
  void setVelocity(int velocity){Velocity = velocity;}
  void setChannel(int channel){Channel = channel;}

  void Send(){
    if(Type == "PC"){
      MIDI.begin();
      MIDI.sendProgramChange(Value, Channel);
    } else if (Type == "CC"){
      MIDI.begin();
      MIDI.sendControlChange(Value, Velocity, Channel);
    }
  };

  // SENDERS
  void SendPC(){
    MIDI.begin();
    MIDI.sendProgramChange(Value, Channel);
  }; 

  void SendCC(){
    MIDI.begin();
    MIDI.sendControlChange(Value, Velocity, Channel);
  };
};

