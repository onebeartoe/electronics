
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
//    const char str[50] = "";
//    const char * str = scrollingText.c_str();
    
    sprintf(str, "dom: %d", dom);
    
    alphaWing->setScrollingText(str);
//    alphaWing->setScrollingText(scrollingText);
}

//void DisplayUpdater::setScrollingText(String text)
//{
//    scrollingText = text;
//    
//    scrollingTextLength = strlen(scrollingText);
//}
