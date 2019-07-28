
#ifndef onebeartoe_InternetClock_h
#define onebeartoe_InternetClock_h

#include "ArduinoLoopTask.h"

#include <WiFiUdp.h>

#include <NTPClient.h>

/**
 * The TimeLib.h dependency is found in the Arduino Library manager under the 
 * name 'Time' by Michael Margolis.
 */
#include <TimeLib.h>

class InternetClock : public ArduinoLoopTask
{
    public: 

        char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        
        int dayOfMonth;
  
        int hour;

        int minute;
        
        InternetClock();
        
        virtual void oneLoop();
};

#endif
