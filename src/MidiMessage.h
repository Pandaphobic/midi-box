#include "Arduino.h"

class MidiMessage {

  public:
    const char* title;
    String type;
    int velocity;
    int value;
    int channel;
};