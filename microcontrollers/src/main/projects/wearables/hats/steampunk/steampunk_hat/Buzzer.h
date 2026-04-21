
#ifndef onebeartoe_Gear_h
#define onebeartoe_Gear_h

#include "/home/luke/Versioning/owner/github/electronics/microcontrollers/src/main/projects/internet-clock/src/ArduinoLoopTask.h"

class Buzzer : public ArduinoLoopTask
{
    public:
        
        int sure; 

        Buzzer();

        virtual void oneLoop();
};

#endif
