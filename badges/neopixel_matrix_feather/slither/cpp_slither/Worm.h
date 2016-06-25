#ifndef onebeartoe_Worm_h
#define onebeartoe_Worm_h

#define WORM_MAX_SEGMENTS 10

class Worm
{
    public:

        Worm(int displayWidth, int displayHeight);

        int length;

        /**
         * The elements at segmentLocations[0][0] and  segmentLocations[0][1] are the (x,y) coordinates of the head of the worm.
         */
        int segmentLocations [WORM_MAX_SEGMENTS][2];// = {0};

        int validMovesCount;
        
        /**
         * This two dimentional array holds the x,y coordinates for a total of 4 possible move locations; up, down, left, and right.
         */
        int validMoves [4][2];

        int displayWidth;
        
        int displayHeight;

        void move();
        

    private:
    
        int color;
        
        int s[WORM_MAX_SEGMENTS][2];

        void updateValidMoves();
};

#endif
