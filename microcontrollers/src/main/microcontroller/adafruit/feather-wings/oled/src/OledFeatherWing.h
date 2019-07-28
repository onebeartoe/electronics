

#ifndef onebeartoe_OledFeatherWing_h
#define onebeartoe_OledFeatherWing_h

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/ArduinoLoopTask.h"

class OledFeatherWing : public ArduinoLoopTask
{
    public:
        
        OledFeatherWing();
        
        virtual void oneLoop();
};

#endif
