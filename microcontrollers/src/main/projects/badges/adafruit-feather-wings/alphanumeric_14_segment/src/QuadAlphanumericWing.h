

#ifndef onebeartoe_InternetClock_h
#define onebeartoe_InternetClock_h

#include RELATIVE_PATH(projects/internet-clock/src/ArduinoLoopTask.h)

class QuadAlphanumericWing : public ArduinoLoopTask
{
    virtual void oneLoop();
};

#endif
