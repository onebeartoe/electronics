
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
    


    
    Serial.println("ploop tix");
    
    dotstarMatrix->show();
}
