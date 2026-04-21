
#include <Arduino.h>

#include "IntervalArduinoLoopTask.h"


IntervalArduinoLoopTask::IntervalArduinoLoopTask()
{
    interval = 5; // very small milliseconds interval so that the loop is always checking the timing
}

virtual void doTheThing();

void IntervalArduinoLoopTask::oneLoop()
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



#endif
