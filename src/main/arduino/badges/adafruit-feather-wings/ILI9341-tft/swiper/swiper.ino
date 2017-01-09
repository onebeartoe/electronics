
#include "license.h"

#include <SPI.h>
#include <Wire.h>      // this is needed even tho we aren't using it

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ILI9341.h> // Hardware-specific library
#include <Adafruit_STMPE610.h>

#include "board-compatibility.h"
#include "tft.h"

bool debugStatements = false;

int oldX = 0;
int xDownCount = 0;
int xUpCount = 0;
int X_INCREMENT_THRESHOLD = 30;

void setup(void) 
{
    Serial.begin(115200);

    delay(10);

    Serial.println("FeatherWing TFT");

    setupTft();
}

void loop() 
{
  // Retrieve a point  
  TS_Point p = ts.getPoint();
  
    if(debugStatements)
    {
        Serial.print("X = "); Serial.print(p.x);
        Serial.print("\tY = "); Serial.print(p.y);
        Serial.print("\tPressure = "); Serial.println(p.z);          
    }

  // Scale from ~0->4000 to tft.width using the calibration #'s
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

  if (p.y < BOXSIZE) 
  {
     oldcolor = currentcolor;

     if (p.x < BOXSIZE) 
     { 
       currentcolor = ILI9341_RED; 
       tft.drawRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
     } else if (p.x < BOXSIZE*2) {
       currentcolor = ILI9341_YELLOW;
       tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
     } else if (p.x < BOXSIZE*3) {
       currentcolor = ILI9341_GREEN;
       tft.drawRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
     } else if (p.x < BOXSIZE*4) {
       currentcolor = ILI9341_CYAN;
       tft.drawRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
     } else if (p.x < BOXSIZE*5) {
       currentcolor = ILI9341_BLUE;
       tft.drawRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
     } else if (p.x < BOXSIZE*6) {
       currentcolor = ILI9341_MAGENTA;
       tft.drawRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
     }

     if (oldcolor != currentcolor) 
     {
        if (oldcolor == ILI9341_RED) 
          tft.fillRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_RED);
        if (oldcolor == ILI9341_YELLOW) 
          tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_YELLOW);
        if (oldcolor == ILI9341_GREEN) 
          tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, ILI9341_GREEN);
        if (oldcolor == ILI9341_CYAN) 
          tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, ILI9341_CYAN);
        if (oldcolor == ILI9341_BLUE) 
          tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, ILI9341_BLUE);
        if (oldcolor == ILI9341_MAGENTA) 
          tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, ILI9341_MAGENTA);
     }
  }

    if (((p.y-PENRADIUS) > 0) && ((p.y+PENRADIUS) < tft.height())) 
    {
        // the current point is in the 'drawing area'
        
        tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
        
        // check for a swipe in the x direction
        xSwipeCheck(p.x);
    }    
}

int const SWIPE_LENGTH = 20;
int swipePoints[SWIPE_LENGTH];

void xSwipeCheck(int currentX)
{
    if(oldX != currentX)
    {
        // the position has changed
        
        if(currentX > oldX)
        {            
            // the X point moved in the down direction (from the SD card slot toward the reset button)
            xDownCount++;
            
            if(xDownCount >= X_INCREMENT_THRESHOLD)
            {
                Serial.print("swipe down detected; x=");
                Serial.println(currentX);
                
                // reset the down count, now that swipe was detected
                xDownCount = 0;
            }
        }
        else
        {            
            // the X point moved in the up direction (from the reset button toward the SD card slot)
            xUpCount++;
            
            if(xUpCount >= X_INCREMENT_THRESHOLD)
            {
                Serial.print("swipe UP detected; x = ");
                Serial.println(currentX);
                
                // reset the up count, now that the swipe was detected
                xUpCount = 0;
            }
        }
    }
    
    // adjust the old X position for the next loop iteration
    oldX = currentX;
}
