
#include "DisplayUpdater.h"

int previousMinute;

DisplayUpdater::DisplayUpdater(InternetClock* clock, 
                               QuadAlphanumericWing* alphaWing)
{
    interval = 20 * 1000; // every 20 seconds
    
    previousMinute = 0;
    
    this->clock = clock;
    
    this->alphaWing = alphaWing;
}

void DisplayUpdater::oneLoop()
{
    char str[50] = "";
    
    if(previousMinute != clock->minute)
    {
        sprintf(str, "%2d%2d", clock->hour, clock->minute);
    
        Serial.print("updating the display with this time: >");
        Serial.print(str);
        Serial.println("<");

        
        alphaWing->setScrollingText(str);
        alphaWing->setWingMode(SCROLLING_TEXT);

        scrollTime();

        alphaWing->setWingMode(STILL);
        alphaWing->setText(str);    
        
        // reset the minute
        previousMinute = clock->minute;
    }
}

void DisplayUpdater::scrollTime()
{
    unsigned long currentMillis = millis();
    
    unsigned long startTime = millis();
     
    long scrollInterval = 2 * 1000; // 5 seconds
    
Serial.print("scroll time");    
Serial.print(alphaWing->scrollingText);    


    while(currentMillis < scrollInterval + startTime) 
    {
        currentMillis = millis();

        alphaWing->loop();
    }
Serial.println();
}
