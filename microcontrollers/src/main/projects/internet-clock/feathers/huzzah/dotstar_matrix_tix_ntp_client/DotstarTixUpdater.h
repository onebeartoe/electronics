
#ifndef onebeartoe_DotstarTixUpdater_h
#define onebeartoe_DotstarTixUpdater_h

#include <Adafruit_DotStarMatrix.h>


#include <DotstarMatrixWing.h>

#include <DotstarTixClock.h>

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/badges/adafruit-feather-wings/alphanumeric_14_segment/src/TextWingModes.h"

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/ArduinoLoopTask.h"

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/InternetClock.h"

//#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/microcontroller/adafruit/feather-wings/dotstar-matrix/src/DotstarMatrixWing.h"

class DotstarTixUpdater : public TextDisplableWing
{
    public:
        
        int previousMinute;
        
        InternetClock* clock;
                
        DotstarTixClock* dotstarWing;
        
        DotstarTixUpdater(InternetClock* clock, DotstarTixClock* dotstarWing);
        
        virtual void oneLoop();

    private:
        
        void updateTime();        
};

#endif
