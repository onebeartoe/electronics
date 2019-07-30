

#ifndef onebeartoe_DotstarMatrixWing_cpp
#define onebeartoe_DotstarMatrixWing_cpp

#include "DotstarMatrixWing.h"

DotstarMatrixWing::DotstarMatrixWing(Adafruit_DotStarMatrix* dotstarMatrix)
{
    interval = 5 * 1000;
    
    this->dotstarMatrix = dotstarMatrix;
}

void DotstarMatrixWing::oneLoop()
{
    
    Serial.println("word");
}

#endif
