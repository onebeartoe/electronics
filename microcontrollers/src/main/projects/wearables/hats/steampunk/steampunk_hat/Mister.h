
#ifndef onebeartoe_Mister_h
#define onebeartoe_Mister_h

#include "/home/roberto/Versioning/owner/github/electronics/microcontrollers/src/main/projects/internet-clock/src/IntervalArduinoLoopTask.h"

class Mister : public IntervalArduinoLoopTask
{
    public:
        
        int sure; 

        Mister();

        virtual void doTheThing();   

        virtual void stopTheThing();
};

#endif
