
#ifndef onebeartoe_Gear_h
#define onebeartoe_Gear_h

#include "/home/luke/Versioning/owner/github/electronics/microcontrollers/src/main/projects/internet-clock/src/ArduinoLoopTask.h"

class Gear : public ArduinoLoopTask
{
    public:
        
        int sure; 

        Gear();

        virtual void oneLoop();
};

#endif
