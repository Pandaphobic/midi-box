#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET LED_BUILTIN    // Reset pin #
#define SCREEN_ADDRESS 0x3C       // 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
String longtype;

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
  display.setTextSize(1);                 // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);    // Draw 'inverse' text
  display.setCursor(0,0);                 // Start at top-left corner
  display.println(longtype);
  display.setTextSize(2);                 // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.print(data); 
  display.print(","); 
  display.print(channel);
  display.display();


  timerOn = true;       
  startTime = millis();
  duration = 5000;
  
}