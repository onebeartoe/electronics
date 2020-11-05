

#ifndef onebeartoe_AdafruitIoTask_h
#define onebeartoe_AdafruitIoTask_h

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/ArduinoLoopTask.h"

class AdafruitIoTask : public ArduinoLoopTask
{
    public:

        AdafruitIoTask(AdafruitIO_Feed * temperatureFeed,
                       float * fahrenheitTemperature);

        virtual void oneLoop();

    private:

        float * temperature;

        AdafruitIO_Feed * temperatureFeed;
};

#endif