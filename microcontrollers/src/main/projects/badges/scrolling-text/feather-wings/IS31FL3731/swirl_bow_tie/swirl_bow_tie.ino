
/**
  * Use 'USBtinyISP' as the programmer. 
  */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

// If you're using the full breakout...
//Adafruit_IS31FL3731 ledmatrix = Adafruit_IS31FL3731();
// If you're using the FeatherWing version
Adafruit_IS31FL3731_Wing ledmatrix = Adafruit_IS31FL3731_Wing();

// The lookup table to make the brightness changes be more visible
uint8_t sweep[] = {1, 2, 3, 4, 6, 8, 10, 15, 20, 30, 40, 60, 60, 40, 30, 20, 15, 10, 8, 6, 4, 3, 2, 1};

void setup() {
  Serial.begin(9600);
  Serial.println("ISSI swirl test");

  if (! ledmatrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 found!");
}

const int matrixColumns = 15;
const int matrixRows = 7;

const int blanksCount = 4;
int blanks [blanksCount][2] = 
{
    {1,1}, 
    {2,2}, 
    {3,3},
    {7,3}
};

void loop() 
{
    // animate over all the pixels, and set the brightness from the sweep table
    for (uint8_t incr = 0; incr < 24; incr++)
    {
        for (uint8_t x = 0; x < matrixColumns; x++)
        {
            for (uint8_t y = 0; y < matrixRows; y++)
            {
                boolean skipLed = false;
                for(int i = 0; i < blanksCount; i++)
                {
                    if(x == blanks[i][0]
                       &&
                       y == blanks[i][1])
                    {
                        skipLed = true;   
                    }
                }
                
                if(skipLed
//                   ||/
//                   (x == 0 && y == 0)
//                   ||
//                   (x==5 && y == 5)
//                   ||
//                   (x == matrixColumns-1 && y == matrixRows-1)
                  )
                {
                    ledmatrix.drawPixel(x, y, 0);
                }
                else
                {
                    
                    ledmatrix.drawPixel(x, y, sweep[(x+y+incr)%24]);
                }              
            }
        }
    }
  
    delay(20);
}
