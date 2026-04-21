
#ifndef onebeartoe_IntervalArduinoLoopTask_h
#define onebeartoe_IntervalArduinoLoopTask_h

#include <Arduino.h>

class IntervalArduinoLoopTask : public ArduinoLoopTask
{
    public:
        
        IntervalArduinoLoopTask();
        
        long intervalStart;

        long intervalDuration;

        virtual void oneLoop();
};

#endif
