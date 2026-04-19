
#ifndef onebeartoe_Mister_h
#define onebeartoe_Mister_h

#include "/home/roberto/Versioning/owner/github/electronics/microcontrollers/src/main/projects/internet-clock/src/ArduinoLoopTask.h"

class Mister : public ArduinoLoopTask
{
    public:
        
        int sure; 

        Mister();

        virtual void oneLoop();
};

#endif
