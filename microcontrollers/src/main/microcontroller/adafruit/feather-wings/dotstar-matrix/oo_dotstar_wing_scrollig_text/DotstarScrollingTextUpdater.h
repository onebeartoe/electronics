
#ifndef onebeartoe_DotstarScrollingTextUpdater_h
#define onebeartoe_DotstarScrollingTextUpdater_h

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/ArduinoLoopTask.h"

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/microcontroller/adafruit/feather-wings/dotstar-matrix/src/DotstarMatrixWing.h"
//#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/microcontroller/adafruit/feather-wings/dotstar-matrix/src/DotstarMatrixWing.cpp"

#include <Adafruit_DotStarMatrix.h>

class DotstarScrollingTextUpdater : public ArduinoLoopTask
{
    public:
    
        static const int MESSAGE_COUNT = 3;
        
        String messages [MESSAGE_COUNT] = {"Go Spurs Go!     ",
                              "Please do not disturb.      ",
                              "Please disturb.        "};
        
        int m;
        
        DotstarMatrixWing* dotstarWing;
        
        DotstarScrollingTextUpdater(DotstarMatrixWing* dotstarWing);
        
        virtual void oneLoop();
};

#endif
