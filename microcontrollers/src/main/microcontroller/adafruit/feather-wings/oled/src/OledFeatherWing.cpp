
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
    
    display.setCursor(0,0);
    
    display.println("boy");

    display.display(); 
    
    if(w > 2)
    {
        interval = 1001;
    }
}
