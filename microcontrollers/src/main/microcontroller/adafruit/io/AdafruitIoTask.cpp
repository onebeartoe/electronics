
#include "AdafruitIoTask.h"

AdafruitIoTask::AdafruitIoTask(float * fahrenheitTemperature)
{
    interval = 1000; // every second
//    interval = 1000 * 5 * 60; // every 5 minutes

    temperature = fahrenheitTemperature;
}

void AdafruitIoTask::oneLoop()
{
    Serial.print("io ploop: ");

    float t = *temperature; // dereference the pointer value

    Serial.println(t);
}
