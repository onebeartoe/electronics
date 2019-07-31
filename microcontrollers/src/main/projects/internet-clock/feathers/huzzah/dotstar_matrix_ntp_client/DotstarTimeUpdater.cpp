
#ifndef onebeartoe_DotstarTimeUpdater_cpp
#define onebeartoe_DotstarTimeUpdater_cpp

#include <Adafruit_DotStarMatrix.h>

#include "DotstarTimeUpdater.h"

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/badges/adafruit-feather-wings/alphanumeric_14_segment/src/TextWingModes.h"

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/InternetClock.h"
//#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/InternetClock.cpp"

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/microcontroller/adafruit/feather-wings/dotstar-matrix/src/DotstarMatrixWing.h"
//#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/microcontroller/adafruit/feather-wings/dotstar-matrix/src/DotstarMatrixWing.cpp"

DotstarTimeUpdater::DotstarTimeUpdater(InternetClock* clock, DotstarMatrixWing* dotstarWing)
{
    interval = 20 * 1000;
    
    this->dotstarWing = dotstarWing;
    
    this->clock = clock;
}

void DotstarTimeUpdater::oneLoop()
{
    char str[50] = "";
    
    if(previousMinute != clock->minute)
    {
        sprintf(str, "%2d%2d", clock->hour, clock->minute);
    
        Serial.print("updating the display with this time: >");
        Serial.print(str);
        Serial.println("<");

        
        dotstarWing->setText(str);
//        dotstarWing->setScrollingText(str);
        dotstarWing->setTextMode(SCROLLING_TEXT);

        scrollTime();

        dotstarWing->setTextMode(STILL);
        dotstarWing->setText(str);    
        
        // reset the minute
        previousMinute = clock->minute;
    }
}

void DotstarTimeUpdater::scrollTime()
//void DotstarTimeUpdater::scrollTime()
{
    unsigned long currentMillis = millis();
    
    unsigned long startTime = millis();
     
    long scrollInterval = 2 * 1000; // 5 seconds
    
Serial.print("scroll time");    
Serial.print(dotstarWing->text);    


    while(currentMillis < scrollInterval + startTime) 
    {
        currentMillis = millis();

        dotstarWing->loop();
    }
Serial.println();
}

#endif
