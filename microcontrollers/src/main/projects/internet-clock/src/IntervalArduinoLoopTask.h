
#ifndef onebeartoe_IntervalArduinoLoopTask_h
#define onebeartoe_IntervalArduinoLoopTask_h

#include <Arduino.h>

#include "ArduinoLoopTask.h"

class IntervalArduinoLoopTask : public ArduinoLoopTask
{
    public:
        
        boolean active = true; //on by default
        
        long intervalStart = 0; // start right away

        long intervalDuration = 1000 * 3; // three seconds

        long inactiveDuration = 1000 * 10; // ten seconds

        IntervalArduinoLoopTask()
        {
            interval = 500 * 1; // every halfsecond run the loop
//            interval = 1000 * 1; // every second run the loop
//TODO:!!!  put this back or find a better default vaule            
//            interval = 5; // very small milliseconds interval so that the loop is always checking the timing
        }        

        virtual void doTheThing();

        virtual void oneLoop()
        {
//            Serial.println("do nothing in IntervalArduinoLoopTask::oneLoop() ");   

            unsigned long currentMillis = millis();

            // check if the interval has started
            if( !active 
                   &&  intervalStart + inactiveDuration <= currentMillis) 
            {
                active = true;

                intervalStart = currentMillis;

                Serial.println("Interval Duration Activated");
            }

            if(active)
            {
                doTheThing();
            }

            // check if the interval has ended
            currentMillis = millis();
            if(active 
                 && intervalStart + intervalDuration <= currentMillis) 
            {
                active = false;

                intervalStart = currentMillis + inactiveDuration;

                Serial.println("Interval Duration Inactived");
            }   
        }
};

#endif
