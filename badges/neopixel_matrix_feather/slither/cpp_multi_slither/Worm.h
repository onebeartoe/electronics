
#ifndef onebeartoe_Worm_h
#define onebeartoe_Worm_h

#define WORM_MAX_SEGMENTS 10

class Worm
{
    public:

        Worm(int displayWidth, int displayHeight, int length);

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
        
        uint16_t segmentColor;

        uint16_t Color(uint8_t r, uint8_t g, uint8_t b);

        /**
         * A pointer to the matrix was needed. For some reason it would not work a concrete object passed as a method parameter.
         */
        void draw(Adafruit_NeoMatrix* matrix);

        void move();
        

    private:
    
        const uint16_t colors[3] = 
        {
            Color(255, 0, 0), 
            Color(0, 255, 0), 
            Color(0, 0, 255) 
        };
        
        int s[WORM_MAX_SEGMENTS][2];

        void updateValidMoves();
};

#endif