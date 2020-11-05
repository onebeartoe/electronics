
#include "AdafruitIoTask.h"

AdafruitIoTask::AdafruitIoTask()
{
    interval = 1000; // every second
//    interval = 1000 * 5 * 60; // every 5 minutes
}

void AdafruitIoTask::oneLoop()
{
    Serial.println("io ploop");
}
