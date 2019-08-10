
#include "DotstarTixClock.h"

void DotstarTixClock::tixClockPositionsVerification()
{
    int x = 0;
    
    int y = 0;
    
    uint16_t segmentColor = dotstarMatrix->Color(5, 5, 155);
    
    dotstarMatrix->drawPixel(x,y, segmentColor);
    
    dotstarMatrix->drawPixel(11, 5, segmentColor);
    
    Serial.println("ploop tix");
    
    dotstarMatrix->show();
}
