

#ifndef onebeartoe_InternetClock_h
#define onebeartoe_InternetClock_h

#include RELATIVE_PATH(projects/internet-clock/src/ArduinoLoopTask.h)


// Demo the quad alphanumeric display LED backpack kit
// scrolls through every character, then scrolls Serial
// input onto the display

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

class QuadAlphanumericWing : public ArduinoLoopTask
{
    public:
        
    char displaybuffer[4] = {' ', ' ', ' ', ' '};
    
    QuadAlphanumericWing();
    
    virtual void demo();
    
    virtual void oneLoop();
};

#endif
