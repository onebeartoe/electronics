
#include "AdafruitIoTask.h"

AdafruitIoTask::AdafruitIoTask(AdafruitIO_Feed * temperatureFeed,
                               float * fahrenheitTemperature)
{
//    interval = 1000; // every second
//    interval = 1000 * 30; // every 30 seconds
//    interval = 1000 * 5 * 60; // every 5 minutes
    interval = 1000 * 10 * 60; // every 10 minutes

    temperature = fahrenheitTemperature;

    this->temperatureFeed = temperatureFeed;
}

void AdafruitIoTask::oneLoop()
{
    Serial.print("io data: ");

    float t = *temperature; // dereference the pointer value

    Serial.println(t);

    bool result = temperatureFeed->save(t);

//Serial.print("feed exists: ");
//Serial.println(temperatureFeed->exists() );

    Serial.print("io saved: ");
    Serial.println(result);
}
