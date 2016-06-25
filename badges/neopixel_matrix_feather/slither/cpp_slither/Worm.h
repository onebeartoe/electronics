#ifndef onebeartoe_Worm_h
#define onebeartoe_Worm_h

#define WORM_MAX_SEGMENTS 10

class Worm
{
    public:

        Worm();

        int getLength();

        int length;

        int segmentLocations [WORM_MAX_SEGMENTS][2];// = {0};

    private:
    
        int color;
        
        int s[WORM_MAX_SEGMENTS][2];
};

#endif
