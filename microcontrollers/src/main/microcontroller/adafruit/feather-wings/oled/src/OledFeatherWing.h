

#ifndef onebeartoe_OledFeatherWing_h
#define onebeartoe_OledFeatherWing_h

#include <Adafruit_SSD1306.h>

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/ArduinoLoopTask.h"

class OledFeatherWing : public ArduinoLoopTask
{
    public:
        
        // we will track if a button is just pressed, just released, or 'currently pressed' 
        byte pressed[NUMBUTTONS], justpressed[NUMBUTTONS], justreleased[NUMBUTTONS];
        
        OledFeatherWing(Adafruit_SSD1306* display);
        
        virtual void oneLoop();
        
//    private:
    
        virtual void check_switches();
};

#endif
