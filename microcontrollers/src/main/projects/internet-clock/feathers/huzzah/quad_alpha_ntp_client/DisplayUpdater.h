
#ifndef onebeartoe_DisplayUpdater_h
#define onebeartoe_DisplayUpdater_h

#include <Arduino.h>

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/ArduinoLoopTask.h"
//#include RELATIVE_PATH(projects/internet-clock/src/ArduinoLoopTask.h)

//TODO: add the IFNDEF sections

class DisplayUpdater : public ArduinoLoopTask
{
    public:
        
    DisplayUpdater();    
        
    virtual void oneLoop();
};


#endif
