
/**
 * Author: Roberto Marquez
 *         https://www.youtube.com/onebeartoe/videos
 *         http://electronics.onebeartoe.org/
 * 
 * My C with classes (C++) was a little rusty, so I used the following as a 
 * resource on how to create a class for reuse:
 *      https://learn.adafruit.com/multi-tasking-the-arduino-part-1/a-classy-solution 
 */

#include "license.h"

#include <SPI.h>
#include <Wire.h>      // this is needed even tho we aren't using it

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ILI9341.h> // Hardware-specific library
#include <Adafruit_STMPE610.h>

//#include "../swiper/board-compatibility.h"
#include "C:\home\owner\versioning\github\electronics\src\main\arduino\adafruit\feather-wings\ILI9341-tft\swiper\swiper\board-compatibility.h"
#include "tft.h"
#include "TftFeatherWing.h"

bool debugStatements = false;

int MODE_DRAWING        = 40;
int MODE_IMAGE_BROWSING = 41;
int mode = MODE_DRAWING;

TftFeatherWing tftAssembly;

void setup(void) 
{
    Serial.begin(115200);

    delay(10);

    Serial.println("FeatherWing TFT");

    setupTft();
    
    // SD Card initialization 
    yield();

    Serial.print("Initializing SD card...");
    if (!SD.begin(SD_CS)) {
      Serial.println("failed!");
    }
    Serial.println("OK!");
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
     } 
     else if (p.x < BOXSIZE*2) 
     {
       currentcolor = ILI9341_YELLOW;
       tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
     } 
     else if (p.x < BOXSIZE*3) 
     {
       currentcolor = ILI9341_GREEN;
       tft.drawRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
     } 
     else if (p.x < BOXSIZE*4) 
     {
       currentcolor = ILI9341_CYAN;
       tft.drawRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
       
       Serial.println("Switching modes to image browsing");
       
       mode = MODE_IMAGE_BROWSING;
     } 
     else if (p.x < BOXSIZE*5) 
     {
       currentcolor = ILI9341_BLUE;
       tft.drawRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
       
       // change back to drawing mode
       mode = MODE_DRAWING;
     } 
     else if (p.x < BOXSIZE*6) 
     {
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

    // check if the touchscreen has a hit on the area that is to the 
    // right of the color/menu selectors
    if (((p.y-PENRADIUS) > 0) && ((p.y+PENRADIUS) < tft.height())) 
    {
        // the current point is in the 'drawing area'
        
        if(mode == MODE_DRAWING)
        {
            tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
        }

        // check for a swipe in the x direction
        boolean swiped = xSwipeCheck(p.x);
        
        if(swiped && mode == MODE_IMAGE_BROWSING)
        {
            Serial.println("gonna draw an image in image mode");
            
//            bmpDraw("red.bmp", 0, 0);
            bmpDraw("purple.bmp", 0, BOXSIZE);
        }
    }    
}
