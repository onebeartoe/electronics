
#ifndef onebeartoe_DotstarTixClock_h
#define onebeartoe_DotstarTixClock_h

#include <DotstarMatrixWing.h>

class DotstarTixClock : public DotstarMatrixWing
{
    public:
        
        // override the parent class constructor
        DotstarTixClock(Adafruit_DotStarMatrix* dotstarMatrix):DotstarMatrixWing(dotstarMatrix){};
        
        virtual void tixClockPositionsVerification();        
};

#endif
