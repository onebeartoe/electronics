
#ifndef onebeartoe_DotstarTixClock_h
#define onebeartoe_DotstarTixClock_h

#include <DotstarMatrixWing.h>

class DotstarTixClock : public DotstarMatrixWing
{
    public:
        
        // override the parent class constructor
        DotstarTixClock(Adafruit_DotStarMatrix* dotstarMatrix):DotstarMatrixWing(dotstarMatrix){};
        
        virtual void tixClockPositionsVerification();
        
        virtual void updateTime(int hour, int minute);


    private:

        int oneRowIndicies[ROWS] = {0, 1, 2, 3, 4, 5};
        
        int hourTensLocations[ROWS][2] = 
        {
            {11,0},
            {11,1},
            {11,2},
            {11,3},
            {11,4},
            {11,5},
        };
        
        int threeRowIndicies[ROWS*3] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
        
        uint16_t hourOnesColor = dotstarMatrix->Color(5, 175, 5);
        
        int hourOnesLocations[ROWS*3][2] = 
        {
            {9,0},
            {9,1},
            {9,2},
            {9,3},
            {9,4},
            {9,5},
            
            {8,0},
            {8,1},
            {8,2},
            {8,3},
            {8,4},
            {8,5},
            
            {7,0},
            {7,1},
            {7,2},
            {7,3},
            {7,4},
            {7,5},            
        };
        
        int twoRowIndicies[ROWS*2] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
        
        int minuteTensLocations[ROWS*2][2] = 
        {
            {5,0},
            {5,1},
            {5,2},
            {5,3},
            {5,4},
            {5,5},
            
            {4,0},
            {4,1},
            {4,2},
            {4,3},
            {4,4},
            {4,5}
        };
        
        int minuteOnesLocations[ROWS*3][2] = 
        {
            {2,0},
            {2,1},
            {2,2},
            {2,3},
            {2,4},
            {2,5},
            
            {1,0},
            {1,1},
            {1,2},
            {1,3},
            {1,4},
            {1,5},
            
            {0,0},
            {0,1},
            {0,2},
            {0,3},
            {0,4},
            {0,5},            
        };

        virtual void updateHourOnes(int hours);
        
        virtual void updateHourTens(int hours);
        
        virtual void updateTimePanel(int count, int rowIndicies[], int locations[][2], uint16_t color);
};

#endif
