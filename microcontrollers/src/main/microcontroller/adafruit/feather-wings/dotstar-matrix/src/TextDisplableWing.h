
#ifndef onebeartoe_TextDisplableWing_h
#define onebeartoe_TextDisplableWing_h

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/ArduinoLoopTask.h"
#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/badges/adafruit-feather-wings/alphanumeric_14_segment/src/TextWingModes.h"

class TextDisplableWing : public ArduinoLoopTask
{
    public:
    
        String text;
        
        TextWingModes mode;
        
        TextDisplableWing();
        
        virtual void setText(String text);
        
        virtual void setTextMode(TextWingModes mode);
        
        virtual void oneLoop();
};
        
#endif
