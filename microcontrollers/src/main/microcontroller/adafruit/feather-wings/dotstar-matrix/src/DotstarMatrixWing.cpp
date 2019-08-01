
#ifndef onebeartoe_DotstarMatrixWing_cpp
#define onebeartoe_DotstarMatrixWing_cpp

#include "DotstarMatrixWing.h"

DotstarMatrixWing::DotstarMatrixWing(Adafruit_DotStarMatrix* dotstarMatrix)
{
    interval = SHIFTDELAY;
    
    text = "GO SPURS GO !    ";

    this->dotstarMatrix = dotstarMatrix;
    
    dotstarMatrix->begin();
    
    dotstarMatrix->setFont(&TomThumb);
    dotstarMatrix->setTextWrap(false);
    dotstarMatrix->setBrightness(BRIGHTNESS);
 
    adaColors[0] = dotstarMatrix->Color(255, 0, 0),   //A red
    adaColors[1] = dotstarMatrix->Color(255, 125, 0), //D orange
    adaColors[2] = dotstarMatrix->Color(200, 255, 0), //A yellowish
    adaColors[3] = dotstarMatrix->Color(0, 255, 0),   //F green
    adaColors[4] = dotstarMatrix->Color(0, 255, 225), //R blue
    adaColors[5] = dotstarMatrix->Color(150, 0, 255), //U purple
    adaColors[6] = dotstarMatrix->Color(255, 0, 220), //I pink
    adaColors[7] = dotstarMatrix->Color(255, 65, 0),  //T reddish
    adaColors[8] = dotstarMatrix->Color(255, 220, 0);  //! orange/yellow

    primaryColors[0] = dotstarMatrix->Color(255, 0, 0);
    primaryColors[1] = dotstarMatrix->Color(0, 255, 0);
    primaryColors[2] = dotstarMatrix->Color(0, 0, 255);
    
    x = dotstarMatrix->width();
}

void DotstarMatrixWing::oneLoop()
{
Serial.println("dotstar scrolling - a");
    x--;

    dotstarMatrix->fillScreen(0);
    dotstarMatrix->setCursor(x, 5);

    int c = 0;

    int iMax = strlen(text.c_str() );

    for (byte i = 0; i < iMax; i++) 
    {
//Serial.println("dotstar scrolling - b");        
        // set the color
        dotstarMatrix->setTextColor(adaColors[c]);

        c++;

        if(c == ADA_COLORS_COUNT)
        {
            c = 0;
        }

        // write the letter
        dotstarMatrix->print(text[i]);
    }

//Serial.println("dotstar scrolling - c");    
    if (x < -xSpread)
    {
        x = dotstarMatrix->width();
    }

    dotstarMatrix->show();
    
Serial.println("dotstar scrolling - d");    
}

void DotstarMatrixWing::primaryDemo()
{
    for (byte i = 0; i < 3; i++) 
    {
        dotstarMatrix->fillScreen(primaryColors[i]);
        dotstarMatrix->show();
        
        delay(500);
    }
}

#endif
