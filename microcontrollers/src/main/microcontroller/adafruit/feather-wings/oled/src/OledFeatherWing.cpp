
#include <Adafruit_SSD1306.h>

#include "OledFeatherWing.h"

Adafruit_SSD1306* oledDisplay;

OledFeatherWing::OledFeatherWing(Adafruit_SSD1306* display)
{
    this->interval = 10;
//    this->interval = 1000;
    
    oledDisplay = display;
}

void OledFeatherWing::oneLoop()
{
//    Serial.println("boy");
    
//    oledDisplay->setCursor(0,0);
//    
//    oledDisplay->println("girl");
//
//    oledDisplay->display(); 
    
    check_switches();      // when we check the switches we'll get the current state

    
  for (byte i = 0; i<NUMBUTTONS; i++){
    if (pressed[i]) 
    {
//      digitalWrite(13, HIGH);
      // is the button pressed down at this moment
        Serial.printf("button %d is pressed.\n", i);
                
    }
    
// the next line is from the original/example code   
oledDisplay->setTextSize(1);
    
    // this is the code block to use for detecting button presses (when the 
    // button is actually releaed).    
    if (justreleased[i])
    {
      if (i == 0)
      {  
        HUE=190;
        Serial.printf("button %d is released.\n", i);
        
//        aButtonPressed();
      }
      else if (i == 1)
      {
        HUE=170;
        Serial.printf("button %d is released.\n", i);

        oledDisplay->clearDisplay();

        oledDisplay->setCursor(0,0);
        oledDisplay->println("Roberto Marquez");
        oledDisplay->println("Dude");
        oledDisplay->print("twiter.com/onebeartoe");
        oledDisplay->println("210 370 7207");
      }
      else if (i == 2)
      {
        HUE=140;
        Serial.printf("button %d is released.\n", i);

        oledDisplay->clearDisplay();

        oledDisplay->setTextSize(2);

        oledDisplay->setCursor(4,2);
        oledDisplay->print("I love you");
//      oledDisplay->startscrollright(0x00, 0x0F);
      }
      else if (i == 3)
      {
        HUE=100;
      }else if (i == 4){
        HUE=70;
      }else if (i == 5){
        HUE=30;
      }
      else if (i == 6)
      {
        HUE=0;
      }
        
      
        for (byte i=0; i<NUMBUTTONS; i++)
        {  
            // remember, check_switches() will necessitate clearing the 'just pressed' flag
            justpressed[i] = 0;
        }
    }
  }
    
//    delay(10);
    yield();
    oledDisplay->display();    
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