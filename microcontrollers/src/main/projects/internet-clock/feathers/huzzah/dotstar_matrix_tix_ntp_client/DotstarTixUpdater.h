
#ifndef onebeartoe_DotstarTimeUpdater_h
#define onebeartoe_DotstarTimeUpdater_h

#include <Adafruit_DotStarMatrix.h>

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/badges/adafruit-feather-wings/alphanumeric_14_segment/src/TextWingModes.h"

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/ArduinoLoopTask.h"

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/InternetClock.h"
//#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/InternetClock.cpp"

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/microcontroller/adafruit/feather-wings/dotstar-matrix/src/DotstarMatrixWing.h"

//#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/microcontroller/adafruit/feather-wings/dotstar-matrix/src/TextDisplableWing.h"
//#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/microcontroller/adafruit/feather-wings/dotstar-matrix/src/TextDisplableWing.cpp"

class DotstarTixUpdater : public TextDisplableWing
{
    public:
        
        int previousMinute;
        
        InternetClock* clock;
                
        DotstarMatrixWing* dotstarWing;
        
        DotstarTixUpdater(InternetClock* clock, DotstarMatrixWing* dotstarWing);
        
        virtual void oneLoop();

    private:
        
        void scrollTime();        
};

#endif
