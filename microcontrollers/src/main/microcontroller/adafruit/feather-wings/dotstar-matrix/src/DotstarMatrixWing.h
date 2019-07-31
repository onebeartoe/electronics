
#ifndef onebeartoe_DotstarMatrixWing_h
#define onebeartoe_DotstarMatrixWing_h

#if defined(ESP8266)
#define DATAPIN    13
#define CLOCKPIN   14
#elif defined(__AVR_ATmega328P__)
#define DATAPIN    2
#define CLOCKPIN   4
#elif defined(ARDUINO_SAMD_FEATHER_M0)
#define DATAPIN    11
#define CLOCKPIN   13
#elif defined(ARDUINO_AVR_FEATHER32U4)
#define DATAPIN    11
#define CLOCKPIN   13
#elif defined(ARDUINO_FEATHER52)
#define DATAPIN    7
#define CLOCKPIN   16
#elif defined(TEENSYDUINO)
#define DATAPIN    9
#define CLOCKPIN   5
#elif defined(ARDUINO_ARCH_WICED)
#define DATAPIN    PA4
#define CLOCKPIN   PB5
#elif defined(ESP32)
#define DATAPIN    27
#define CLOCKPIN   13
#endif

#define BRIGHTNESS 3

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
        
        const int SHIFTDELAY = 200;

        uint16_t primaryColors[3];
        
        Adafruit_DotStarMatrix* dotstarMatrix;
        
        DotstarMatrixWing(Adafruit_DotStarMatrix* dotstarMatrix);

        int x;
        
        static const int ADA_COLORS_COUNT = 9;
        
        uint16_t adaColors[ADA_COLORS_COUNT];
        
        virtual void primaryDemo();
        
        virtual void oneLoop();
};

#endif
