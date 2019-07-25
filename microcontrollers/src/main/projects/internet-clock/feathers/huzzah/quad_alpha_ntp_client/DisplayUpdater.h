
#ifndef onebeartoe_DisplayUpdater_h
#define onebeartoe_DisplayUpdater_h

#include <Arduino.h>

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/ArduinoLoopTask.h"

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/InternetClock.h"

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/badges/adafruit-feather-wings/alphanumeric_14_segment/src/QuadAlphanumericWing.h"

class DisplayUpdater : public ArduinoLoopTask
{
    public:
        
        InternetClock* clock;

        QuadAlphanumericWing* alphaWing;

        String scrollingText;
//        char scrollingText[50];
        
        DisplayUpdater(InternetClock* clock, QuadAlphanumericWing* alphaWing);    

        virtual void oneLoop();
        
//        virtual void setScrollingText(String text);
//        virtual void setScrollingText(char text []);
};

#endif
