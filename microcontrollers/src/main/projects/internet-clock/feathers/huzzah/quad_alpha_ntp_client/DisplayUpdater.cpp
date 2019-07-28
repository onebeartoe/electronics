
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
    int dom = clock->dayOfMonth;
    
    char str[50] = "";
    
    sprintf(str, "dom: %d", dom);
    
//    alphaWing->setScrollingText(str);

    sprintf(str, "%2d%2d", clock->hour, clock->minute);
    
    Serial.print("updating the display with this time: >");
    Serial.print(str);
    Serial.println("<");
    
    alphaWing->setText(str);
//    alphaWing->setText("[__]");
}
