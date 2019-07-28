

#ifndef onebeartoe_OledFeatherWing_h
#define onebeartoe_OledFeatherWing_h

#include <Adafruit_SSD1306.h>

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/ArduinoLoopTask.h"

// here is where we define the buttons that we'll use. button "1" is the first, button "6" is the 6th, etc
byte buttons[] = {BUTTON_A, BUTTON_B, BUTTON_C}; 

// This handy macro lets us determine how big the array up above is, by checking the size
#define NUMBUTTONS sizeof(buttons)


class OledFeatherWing : public ArduinoLoopTask
{
    public:
        
        // we will track if a button is just pressed, just released, or 'currently pressed' 
        byte pressed[NUMBUTTONS], justpressed[NUMBUTTONS], justreleased[NUMBUTTONS];
        
        OledFeatherWing(Adafruit_SSD1306* display);
    
        virtual void aButtonPressed();
        
        virtual void oneLoop();
    
        virtual void check_switches();
        
//    private:
};

#endif
