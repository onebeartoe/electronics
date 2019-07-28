
#include "OledFeatherWing.h"

OledFeatherWing::OledFeatherWing()
{
    this->interval = 1000;
}

int w = 3;

void OledFeatherWing::oneLoop()
{
    Serial.println("boy");
    
    
    
    if(w > 2)
    {
        interval = 1001;
    }
}
