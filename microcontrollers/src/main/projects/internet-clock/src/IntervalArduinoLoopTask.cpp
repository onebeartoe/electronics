
#include <Arduino.h>

#include "IntervalArduinoLoopTask.h"


IntervalArduinoLoopTask::IntervalArduinoLoopTask()
{
    interval = 5; // very small milliseconds interval so that the loop is always checking the timing
}

virtual void doTheThing();





#endif
