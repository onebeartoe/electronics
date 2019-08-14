
#ifndef onebeartoe_DotstarTixClock_h
#define onebeartoe_DotstarTixClock_h

#include <DotstarMatrixWing.h>

class DotstarTixClock : public DotstarMatrixWing
{
    public:
        
        
        
        // override the parent class constructor
        DotstarTixClock(Adafruit_DotStarMatrix* dotstarMatrix):DotstarMatrixWing(dotstarMatrix){};
        
        virtual void tixClockPositionsVerification();


    private:
        
        int hourTensLocations[ROWS][2] = 
        {
            {11,0},
            {11,1},
            {11,2},
            {11,3},
            {11,4},
            {11,5},            
        };
};

#endif
