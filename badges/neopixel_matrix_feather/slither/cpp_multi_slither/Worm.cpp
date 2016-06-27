
#include <Adafruit_NeoMatrix.h>

#include "Arduino.h"
#include "Worm.h"

Worm::Worm(int displayWidth, int displayHeight, int length)
{
    this->length = length;

    this->displayWidth = displayWidth;
    this->displayHeight = displayHeight;
}

uint16_t Worm::Color(uint8_t r, uint8_t g, uint8_t b) 
{
  return ((uint16_t)(r & 0xF8) << 8) |
         ((uint16_t)(g & 0xFC) << 3) |
                    (b         >> 3);
}

void Worm::draw(Adafruit_NeoMatrix* matrix)
{
    // go over each worm segment
    for(int i=0; i<length; i++)
    {        
        int x = segmentLocations[i][0];
        int y = segmentLocations[i][1];

        matrix->drawPixel(x,y, colors[2]);
    }
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