
#include <Adafruit_DotStarMatrix.h>

/**
 * The following includes are provided by onebeartoe.org and are located in this same 
 * source code repository.DotstarMatrixWing
 * 
 * For each .h file listed, cd into the containing directory and execute the 
 * 'install-library.sh' script to 'install' into the local Arduino libraries 
 * directory.
 */
#include <DotstarTixClock.h>

#include "DotstarTixUpdater.h"

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/InternetClock.h"
#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/InternetClock.cpp"

Adafruit_DotStarMatrix matrix = Adafruit_DotStarMatrix(12, 6, 
                                                       DATAPIN, CLOCKPIN,
                                                       DS_MATRIX_BOTTOM + DS_MATRIX_LEFT + DS_MATRIX_ROWS + DS_MATRIX_PROGRESSIVE,
                                                       DOTSTAR_BGR);

InternetClock clock;

DotstarTixClock dostarTixClock(&matrix);

DotstarTixUpdater displayUpdater(&clock, &dostarTixClock);

void setup() 
{
    Serial.begin(9600);

    Serial.println("tix clock - dotstar matrix wing ntp client");
        
    // set a smaller spread than the default since there text string is short (only 4 chars)
//    dostarTixClock.xSpread = 20;
    
    dostarTixClock.tixClockPositionsVerification();
}

void loop()
{
    clock.loop();

    displayUpdater.loop();
}
