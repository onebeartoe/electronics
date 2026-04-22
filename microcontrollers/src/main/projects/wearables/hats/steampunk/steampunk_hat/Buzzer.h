
#ifndef onebeartoe_Buzzer_h
#define onebeartoe_Buzzer_h

#include "/home/roberto/Versioning/owner/github/electronics/microcontrollers/src/main/projects/internet-clock/src/ArduinoLoopTask.h"

class Buzzer : public ArduinoLoopTask
{
    public:
        
        int sure; 

        Buzzer();

        virtual void oneLoop();
};

#endif
