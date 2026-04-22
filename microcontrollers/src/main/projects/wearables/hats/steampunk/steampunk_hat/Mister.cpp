
#include <Arduino.h>

//!!!!
#include "/home/roberto/Versioning/owner/github/electronics/microcontrollers/src/main/projects/internet-clock/src/IntervalArduinoLoopTask.h"


#include "Mister.h"



Mister::Mister()
{
}

// void Mister::oneLoop()
// {
//     IntervalArduinoLoopTask::oneLoop();
// }

void Mister::doTheThing()
{
    Serial.println("doing the thing in Mister");   
}
