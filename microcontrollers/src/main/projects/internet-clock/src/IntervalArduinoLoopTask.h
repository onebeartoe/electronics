
#ifndef onebeartoe_IntervalArduinoLoopTask_h
#define onebeartoe_IntervalArduinoLoopTask_h

#include <Arduino.h>

#include "ArduinoLoopTask.h"

class IntervalArduinoLoopTask : public ArduinoLoopTask
{
    public:
        
        IntervalArduinoLoopTask();

        boolean active = true; //on by default
        
        long intervalStart = 0; // start right away

        long intervalDuration = 1000 * 3; // three seconds

        long inactiveDuration = 1000 * 10; // ten seconds

        virtual void oneLoop();
};

#endif
