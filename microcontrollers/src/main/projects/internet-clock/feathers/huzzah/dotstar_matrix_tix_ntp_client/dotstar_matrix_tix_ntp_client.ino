
#include <Adafruit_DotStarMatrix.h>

/**
 * The following includes are provided by onebeartoe.org and are located in this same 
 * source code repository.
 * 
 * For each .h file listed, cd into the containing directory and execute the 
 * 'install-library.sh' script to 'install' into the local Arduino libraries 
 * directory.
 */
#include <DotstarTixClock.h>

#include "DotstarTixUpdater.h"

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/InternetClock.h"
#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/InternetClock.cpp"

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/microcontroller/adafruit/feather-wings/dotstar-matrix/src/DotstarMatrixWing.h"
#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/microcontroller/adafruit/feather-wings/dotstar-matrix/src/DotstarMatrixWing.cpp"

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/microcontroller/adafruit/feather-wings/dotstar-matrix/src/TextDisplableWing.h"
#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/microcontroller/adafruit/feather-wings/dotstar-matrix/src/TextDisplableWing.cpp"

Adafruit_DotStarMatrix matrix = Adafruit_DotStarMatrix(12, 6, 
                                                       DATAPIN, CLOCKPIN,
                                                       DS_MATRIX_BOTTOM + DS_MATRIX_LEFT + DS_MATRIX_ROWS + DS_MATRIX_PROGRESSIVE,
                                                       DOTSTAR_BGR);

InternetClock clock;

DotstarMatrixWing dotstarWing(&matrix);

DotstarTixUpdater displayUpdater(&clock, &dotstarWing);

void setup() 
{
    Serial.begin(9600);

    Serial.println("tix clock - dotstar matrix wing ntp client");
    
    Serial.println(wwwww);
    
    // set a smaller spread than the default since there text string is short (only 4 chars)
    dotstarWing.xSpread = 20;
    
    dotstarWing.tixClockPositionsVerification();
}

void loop()
{
    clock.loop();

//TODO: enable this once the tix positioning verification is done    
//    displayUpdater.loop();
}
