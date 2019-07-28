
#ifndef onebeartoe_QuadAlphanumericWing_h
#define onebeartoe_QuadAlphanumericWing_h

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/ArduinoLoopTask.h"
//#include RELATIVE_PATH(projects/internet-clock/src/ArduinoLoopTask.h)


// Demo the quad alphanumeric display LED backpack kit
// scrolls through every character, then scrolls Serial
// input onto the display

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

enum WingMode
{
    BLANK,
    SCROLLING_TEXT,
    SERIAL_INPUT,
    STILL
};

class QuadAlphanumericWing : public ArduinoLoopTask
{
    public:
        
        char displaybuffer[4] = {' ', ' ', ' ', ' '};

        String scrollingText = " hellow world -  ";
        
        int scrollingTextLength;
        
        WingMode wingMode;

        QuadAlphanumericWing();

        virtual void demo();

        virtual void oneLoop();

        virtual void setScrollingText(String text);
        
        virtual void setText(String text);
        
        virtual void setWingMode(WingMode mode);
    
    private:
    
        
        
        void scrollText();
        
        void serialInput();
};

#endif
