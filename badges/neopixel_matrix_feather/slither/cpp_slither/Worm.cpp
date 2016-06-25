
#include "Arduino.h"
#include "Worm.h"

Worm::Worm(int displayWidth, int displayHeight)
{
    this->length = 2;

    this->displayWidth = displayWidth;
    this->displayHeight = displayHeight;
}

void Worm::move()
{
    for(int i=length-1; i>0; i--)
    {
        segmentLocations[i][0] = segmentLocations[i-1][0];
        segmentLocations[i][1] = segmentLocations[i-1][1];
    }

    updateValidMoves();

    int m = random(0, validMovesCount);

    int x = validMoves[m][0];
    int y = validMoves[m][1];

    segmentLocations[0][0] = x;
    segmentLocations[0][1] = y;
}

void Worm::updateValidMoves()
{
    int headX = segmentLocations[0][0];
    int headY = segmentLocations[0][1];

    int i = 0;

    // up
    if(headY > 0)
    {
        validMoves[i][1] = headY - 1;
        validMoves[i][0] = headX;
        
        i++;
    }

    // down
    if(headY < displayHeight-1)
    {
        validMoves[i][1] = headY + 1;
        validMoves[i][0] = headX;

        i++;
    }
    
    // left
    if(headX > 0)
    {
        validMoves[i][0] = headX - 1;
        validMoves[i][1] = headY;

        i++;
    }

    // right
    if(headX < displayWidth-1)
    {
        validMoves[i][0] = headX + 1;
        validMoves[i][1] = headY;

        i++;
    }

    validMovesCount = i;
}
