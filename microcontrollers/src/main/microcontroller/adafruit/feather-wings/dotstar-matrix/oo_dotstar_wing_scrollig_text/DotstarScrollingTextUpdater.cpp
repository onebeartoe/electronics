
#include "DotstarScrollingTextUpdater.h"

#include <Adafruit_DotStarMatrix.h>

DotstarScrollingTextUpdater::DotstarScrollingTextUpdater(DotstarMatrixWing* dotstarWing)
{
    interval = 15 * 1000; // fifteen seconds
    
    m = 0;
    
    this->dotstarWing = dotstarWing;
}

void DotstarScrollingTextUpdater::oneLoop()
{
    Serial.println("changing the message");
    
    dotstarWing->setText( messages[m] );
    
    m++;
    
    if(m == MESSAGE_COUNT)
    {
        m = 0;
    }
}
