

#ifndef onebeartoe_DotstarMatrixWing_cpp
#define onebeartoe_DotstarMatrixWing_cpp

#include "DotstarMatrixWing.h"

DotstarMatrixWing::DotstarMatrixWing(Adafruit_DotStarMatrix* dotstarMatrix)
{
    interval = SHIFTDELAY;
//    interval = 5 * 1000;
    
    this->dotstarMatrix = dotstarMatrix;
 
    adaColors[0] = dotstarMatrix->Color(255, 0, 0),   //A red
    adaColors[1] = dotstarMatrix->Color(255, 125, 0), //D orange
    adaColors[2] = dotstarMatrix->Color(200, 255, 0), //A yellowish
    adaColors[3] = dotstarMatrix->Color(0, 255, 0),   //F green
    adaColors[4] = dotstarMatrix->Color(0, 255, 225), //R blue
    adaColors[5] = dotstarMatrix->Color(150, 0, 255), //U purple
    adaColors[6] = dotstarMatrix->Color(255, 0, 220), //I pink
    adaColors[7] = dotstarMatrix->Color(255, 65, 0),  //T reddish
    adaColors[8] = dotstarMatrix->Color(255, 220, 0);  //! orange/yellow
    
    x = dotstarMatrix->width();
}

void DotstarMatrixWing::oneLoop()
{  
//    Serial.println("word");
    
    char scrollingText[] = "GO SPURS GO!    ";
//    char scrollingText[13] = "GO SPURS GO!";

//    int x = dotstarMatrix->width();
  
    x--;
    
//    if(x)
//    for( ; x > -50; x-- )
    {
        dotstarMatrix->fillScreen(0);
        dotstarMatrix->setCursor(x, 5);
        
        for (byte i = 0; i < 9; i++) 
        {
            // set the color
            dotstarMatrix->setTextColor(adaColors[i]);
            // write the letter
            dotstarMatrix->print(scrollingText[i]);
        }

        if (x < -50)
//        if (--x < -50)
        {
            x = dotstarMatrix->width();
        }

        dotstarMatrix->show();
        
//        delay(SHIFTDELAY);  
    }

//    delay(500);    
}

#endif
