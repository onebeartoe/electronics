
#ifndef onebeartoe_IntervalArduinoLoopTask_h
#define onebeartoe_IntervalArduinoLoopTask_h

#include <Arduino.h>

#include "ArduinoLoopTask.h"

class IntervalArduinoLoopTask : public ArduinoLoopTask
{
    public:
        
//        IntervalArduinoLoopTask();

        boolean active = true; //on by default
        
        long intervalStart = 0; // start right away

        long intervalDuration = 1000 * 3; // three seconds

        long inactiveDuration = 1000 * 10; // ten seconds



IntervalArduinoLoopTask()
//IntervalArduinoLoopTask::IntervalArduinoLoopTask()
{
    interval = 5; // very small milliseconds interval so that the loop is always checking the timing
}        

//        virtual void oneLoop();

virtual void doTheThing();

    virtual 
    void oneLoop()
//    void IntervalArduinoLoopTask::oneLoop()
    {
        Serial.println("do nothing in IntervalArduinoLoopTask::oneLoop() ");   

        unsigned long currentMillis = millis();

        // check if the interval has started
        if(currentMillis - intervalStart > intervalDuration) 
        {
            active = true;

            intervalStart = currentMillis;
        }

        if(active)
        {
            doTheThing();
        }

        // check if the interval has ended
        currentMillis = millis();
        if(intervalStart + intervalDuration >= currentMillis) 
        {
            active = false;

            intervalStart = currentMillis + inactiveDuration;
        }   
    }



};

#endif
