
#ifndef onebeartoe_Mister_h
#define onebeartoe_Mister_h

#include "/home/luke/Versioning/owner/github/electronics/microcontrollers/src/main/projects/internet-clock/src/IntervalArduinoLoopTask.h"
//#include "/home/luke/Versioning/owner/github/electronics/microcontrollers/src/main/projects/internet-clock/src/ArduinoLoopTask.h"

class Mister : public IntervalArduinoLoopTask
{
    public:
        
        int sure; 

        Mister();

        virtual void doTheThing();   
    

//        virtual void oneLoop();
};

#endif
