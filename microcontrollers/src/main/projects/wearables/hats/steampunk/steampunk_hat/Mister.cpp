
#include <Arduino.h>

#include "/home/roberto/Versioning/owner/github/electronics/microcontrollers/src/main/projects/internet-clock/src/IntervalArduinoLoopTask.h"

#include "Mister.h"

Mister::Mister()
{
}

void Mister::doTheThing()
{
    Serial.println("Doing the thing in Mister");   
}

void Mister::stopTheThing()
{
    Serial.println("Stopping the thing in Mister");   
}
