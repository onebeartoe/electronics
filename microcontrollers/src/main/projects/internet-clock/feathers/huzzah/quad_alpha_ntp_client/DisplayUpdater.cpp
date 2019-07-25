
#include "DisplayUpdater.h"

DisplayUpdater::DisplayUpdater(InternetClock* clock, 
                               QuadAlphanumericWing* alphaWing)
{
    interval = 2 * 1000; // every 2 seconds
    
    this->clock = clock;
    
    this->alphaWing = alphaWing;
}

void DisplayUpdater::oneLoop()
{
    int i = 2;
    
//    Serial.println("updating display");
}
