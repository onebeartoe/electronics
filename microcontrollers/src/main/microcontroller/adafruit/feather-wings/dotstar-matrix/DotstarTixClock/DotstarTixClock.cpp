
#include "DotstarTixClock.h"

void DotstarTixClock::tixClockPositionsVerification()
{
    int displayDelay = 400;

    uint16_t hourTensColor = dotstarMatrix->Color(5, 5, 155);
    
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
    
    uint16_t hourOnesColor = dotstarMatrix->Color(5, 175, 5);

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
    
    uint16_t minuteTensColor = dotstarMatrix->Color(185, 5, 5);

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

    uint16_t minuteOnesColor = dotstarMatrix->Color(151, 48, 177);
    
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
    
}