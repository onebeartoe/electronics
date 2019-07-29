
#ifndef onebeartoe_DotstarMatrixWing_h
#define onebeartoe_DotstarMatrixWing_h

#include <Adafruit_DotStar.h>

// https://www.adafruit.com/product/3449
// https://learn.adafruit.com/adafruit-dotstar-featherwing-adafruit

// Adafruit_DotStarMatrix example for single DotStar LED matrix.
// Scrolls 'Adafruit' across the matrix.

#include <SPI.h>
#include <Adafruit_GFX.h>

/**
 * the next dependency is from
 * 
 *      https://github.com/adafruit/Adafruit_DotStarMatrix
 */
#include <Adafruit_DotStarMatrix.h>

#include <Adafruit_DotStar.h>
#include <Fonts/TomThumb.h>

//#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/badges/adafruit-feather-wings/alphanumeric_14_segment/src/WingModes.h"
#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/ArduinoLoopTask.h"

class DotstarMatrixWing : public ArduinoLoopTask
{
    public:
        
        DotstarMatrixWing();
        
        virtual void oneLoop();
};

#endif
