
#include <Adafruit_DotStarMatrix.h>

#include "DotstarTimeUpdater.h"
//#include "DotstarTimeUpdater.cpp"

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

DotstarTimeUpdater displayUpdater(&clock, &dotstarWing);

void setup() 
{
    Serial.begin(9600);

    Serial.println("dotstar matrix wing ntp client");
}

void loop()
{
    clock.loop();
    
    displayUpdater.loop();
}