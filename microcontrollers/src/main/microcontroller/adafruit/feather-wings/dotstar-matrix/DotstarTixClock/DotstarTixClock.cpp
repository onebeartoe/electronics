
#include <cstdlib> // for std::srand()

#include <algorithm> // for std::random_shuffle()

#include "DotstarTixClock.h"

void DotstarTixClock::tixClockPositionsVerification()
{
    int displayDelay = 250;
    
    for(int i = 0; i<ROWS; i++)
    {
        int x = hourTensLocations[i][0];

        int y = hourTensLocations[i][1];
        
        Serial.print(x);        
        Serial.print(",");        
        Serial.println(y);
        
        dotstarMatrix->drawPixel(x,y, hourTensColor);       
        
        dotstarMatrix->show();
        
        delay(displayDelay);
    }

    for(int i = 0; i<ROWS*3; i++)
    {
        int x = hourOnesLocations[i][0];

        int y = hourOnesLocations[i][1];
        
        Serial.print(x);        
        Serial.print(",");        
        Serial.println(y);
        
        dotstarMatrix->drawPixel(x,y, hourOnesColor);
        
        dotstarMatrix->show();
        
        delay(displayDelay);
    }

    for(int i = 0; i<ROWS*2; i++)
    {
        int x = minuteTensLocations[i][0];

        int y = minuteTensLocations[i][1];
        
        Serial.print(x);        
        Serial.print(",");        
        Serial.println(y);
        
        dotstarMatrix->drawPixel(x,y, minuteTensColor);       
        
        dotstarMatrix->show();
        
        delay(displayDelay);
    }
    
    for(int i = 0; i<ROWS*3; i++)
    {
        int x = minuteOnesLocations[i][0];

        int y = minuteOnesLocations[i][1];
        
        Serial.print(x);        
        Serial.print(",");        
        Serial.println(y);
        
        dotstarMatrix->drawPixel(x,y, minuteOnesColor);       
        
        dotstarMatrix->show();
        
        delay(displayDelay);
    }    
    
    Serial.println("ploop tix");
}

void DotstarTixClock::updateTime(int hour, int minute)
{
    updateHourOnes(hour);
    
    updateHourTens(hour);
    
    updateMinuteTens(minute);
    
    updateMinuteOnes(minute);
}

void DotstarTixClock::updateHourOnes(int hours)
{
    int hourOnes = hours % 10;
    
    Serial.println();
    Serial.print("hourOnes -> ");
    Serial.println(hourOnes);

    // I haven't figured out how to shuffle the array insdie the call to updatTimePanel()    
    std::random_shuffle(threeRowIndicies, threeRowIndicies + (sizeof(threeRowIndicies) / sizeof(*threeRowIndicies)));
    
    updateTimePanel(hourOnes, threeRowIndicies, hourOnesLocations, hourOnesColor);
}

void DotstarTixClock::updateHourTens(int hours)
{
    int hourTens = hours / 10;
    
    Serial.print("hourTens -> ");
    Serial.println(hourTens);
 
    // shuffle the indicies
    std::random_shuffle(oneRowIndicies, oneRowIndicies + (sizeof(oneRowIndicies) / sizeof(*oneRowIndicies)));
    
    updateTimePanel(hourTens, oneRowIndicies, hourTensLocations, hourTensColor);
}


void DotstarTixClock::updateMinuteOnes(int minutes)
{
    int minuteOnes = minutes % 10;
    
    Serial.print("minuteOnes -> ");
    Serial.println(minuteOnes);
    
    std::random_shuffle(threeRowIndicies, threeRowIndicies + (sizeof(threeRowIndicies) / sizeof(*threeRowIndicies)));

    updateTimePanel(minuteOnes, threeRowIndicies, minuteOnesLocations, minuteOnesColor);
}

void DotstarTixClock::updateMinuteTens(int minutes)
{
    int minuteTens = minutes / 10;
    
    Serial.print("minuteTens -> ");
    Serial.println(minuteTens);
    
    std::random_shuffle(twoRowIndicies, twoRowIndicies + (sizeof(twoRowIndicies) / sizeof(*twoRowIndicies)));
    
    updateTimePanel(minuteTens, twoRowIndicies, minuteTensLocations, minuteTensColor);
}

void DotstarTixClock::updateTimePanel(int count, int rowIndicies[], int locations[][2], uint16_t color)
{
    // doh!  I could not figure what was going with the rowIndicies not acutally shuffling
    // I suspect the rowIndicies was passed by value and not reference
//    std::random_shuffle(rowIndicies, rowIndicies + (sizeof(rowIndicies) / sizeof(*rowIndicies)));
    
    for(int ho = 0; ho < count; ho++)
    {
        int i = rowIndicies[ho];
        
        int x = locations[i][0];
        
        int y = locations[i][1];
        
        dotstarMatrix->drawPixel(x,y, color);
    }    
}
