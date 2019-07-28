
#include <Adafruit_SSD1306.h>

#include "OledFeatherWing.h"

Adafruit_SSD1306* oledDisplay;

OledFeatherWing::OledFeatherWing(Adafruit_SSD1306* display)
{
    this->interval = 1000;
    
    oledDisplay = display;
}

int w = 3;

void OledFeatherWing::oneLoop()
{
    Serial.println("boy");
    
    oledDisplay->setCursor(0,0);
    
    oledDisplay->println("girl");

    oledDisplay->display(); 
    
    if(w > 2)
    {
        interval = 1001;
    }
}

void OledFeatherWing::check_switches()
{
  static byte previousstate[NUMBUTTONS];
  static byte currentstate[NUMBUTTONS];
  static long lasttime;
  byte index;

  if (millis() < lasttime){ // we wrapped around, lets just try again
     lasttime = millis();
  }
  
  if ((lasttime + DEBOUNCE) > millis()) 
  {
    // not enough time has passed to debounce
    return; 
  }
  
  // ok we have waited DEBOUNCE milliseconds, lets reset the timer
  lasttime = millis();
  
  for (index = 0; index<NUMBUTTONS; index++){ // when we start, we clear out the "just" indicators
    justreleased[index] = 0;
     
    currentstate[index] = digitalRead(buttons[index]);   // read the button
   
    if (currentstate[index] == previousstate[index]) {
      if ((pressed[index] == LOW) && (currentstate[index] == LOW)) {
          // just pressed
          justpressed[index] = 1;
      }
      else if ((pressed[index] == HIGH) && (currentstate[index] == HIGH)) {
          // just released
          justreleased[index] = 1;
      }
      pressed[index] = !currentstate[index];  // remember, digital HIGH means NOT pressed
    }
    //Serial.println(pressed[index], DEC);
    previousstate[index] = currentstate[index];   // keep a running tally of the buttons
  }
}