
#ifndef onebeartoe_IntervalArduinoLoopTask_h
#define onebeartoe_IntervalArduinoLoopTask_h

#include <Arduino.h>

class IntervalArduinoLoopTask : public ArduinoLoopTask
{
    public:
        
        IntervalArduinoLoopTask();
        // {
        //     
        // }

        virtual void oneLoop();
};

#endif
