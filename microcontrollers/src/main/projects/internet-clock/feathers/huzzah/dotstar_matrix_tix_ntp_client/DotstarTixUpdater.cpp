
#ifndef onebeartoe_DotstarTixUpdater_cpp
#define onebeartoe_DotstarTixUpdater_cpp

#include <Adafruit_DotStarMatrix.h>

#include "DotstarTixUpdater.h"

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/badges/adafruit-feather-wings/alphanumeric_14_segment/src/TextWingModes.h"

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/InternetClock.h"

//#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/microcontroller/adafruit/feather-wings/dotstar-matrix/src/DotstarMatrixWing.h"

DotstarTixUpdater::DotstarTixUpdater(InternetClock* clock, DotstarTixClock* dotstarWing)
{
    interval = 20 * 1000;
    
    this->dotstarWing = dotstarWing;

    this->clock = clock;
}

void DotstarTixUpdater::oneLoop()
{
    char str[50] = "";
  
    dotstarWing->dotstarMatrix->fillScreen(0);
    
    sprintf(str, "%2d%2d", clock->hour, clock->minute);

    Serial.println();
    Serial.print("updating the display with this time: >");
    Serial.print(str);
    Serial.println("<");

    dotstarWing->updateTime(clock->hour, clock->minute);

    dotstarWing->dotstarMatrix->show();

    // reset the minute
    previousMinute = clock->minute;
}

#endif
