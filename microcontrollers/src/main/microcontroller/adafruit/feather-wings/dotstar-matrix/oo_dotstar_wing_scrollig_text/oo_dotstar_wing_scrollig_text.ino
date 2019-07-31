
#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/microcontroller/adafruit/feather-wings/dotstar-matrix/src/DotstarMatrixWing.h"
#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/microcontroller/adafruit/feather-wings/dotstar-matrix/src/DotstarMatrixWing.cpp"

#include <Adafruit_DotStarMatrix.h>

// MATRIX DECLARATION:
// Parameter 1 = width of DotStar matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   DS_MATRIX_TOP, DS_MATRIX_BOTTOM, DS_MATRIX_LEFT, DS_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     DS_MATRIX_TOP + DS_MATRIX_LEFT for the top-left corner.
//   DS_MATRIX_ROWS, DS_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   DS_MATRIX_PROGRESSIVE, DS_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type:
//   DOTSTAR_BRG  Pixels are wired for BRG bitstream (most DotStar items)
//   DOTSTAR_GBR  Pixels are wired for GBR bitstream (some older DotStars)
//   DOTSTAR_BGR  Pixels are wired for BGR bitstream (APA102-2020 DotStars)
Adafruit_DotStarMatrix matrix = Adafruit_DotStarMatrix(12, 6, 
                                                       DATAPIN, CLOCKPIN,
                                                       DS_MATRIX_BOTTOM + DS_MATRIX_LEFT + DS_MATRIX_ROWS + DS_MATRIX_PROGRESSIVE,
                                                       DOTSTAR_BGR);

DotstarMatrixWing dotstarWing(&matrix);

void setup() 
{
    Serial.begin(115200);

    Serial.println("\nDotstar Matrix Wing");

    Serial.print("using DATAPIN: ");
    Serial.println(DATAPIN);
    
    Serial.print("using CLOCKPIN: ");
    Serial.println(CLOCKPIN);
    
    dotstarWing.primaryDemo();
}

void loop()
{
    dotstarWing.loop();
}
