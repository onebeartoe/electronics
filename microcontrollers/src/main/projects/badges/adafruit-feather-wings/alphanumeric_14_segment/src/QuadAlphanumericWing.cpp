
#include "QuadAlphanumericWing.h"

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

char text [] = " hellow world -  ";

int scrollingTextLength;

int scrollingTextIndex;

QuadAlphanumericWing::QuadAlphanumericWing()
{
    scrollingTextLength = strlen(text);
    
    interval = 350;
    
    wingMode = SCROLLING_TEXT;
    
    alpha4.begin(0x70);  // pass in the address

    alpha4.writeDigitRaw(3, 0x0);
    alpha4.writeDigitRaw(0, 0xFFFF);
    alpha4.writeDisplay();
    delay(200);
    alpha4.writeDigitRaw(0, 0x0);
    alpha4.writeDigitRaw(1, 0xFFFF);
    alpha4.writeDisplay();
    delay(200);
    alpha4.writeDigitRaw(1, 0x0);
    alpha4.writeDigitRaw(2, 0xFFFF);
    alpha4.writeDisplay();
    delay(200);
    alpha4.writeDigitRaw(2, 0x0);
    alpha4.writeDigitRaw(3, 0xFFFF);
    alpha4.writeDisplay();
    delay(200);

    alpha4.clear();
    alpha4.writeDisplay();    
}

void QuadAlphanumericWing::demo()
{
    // display every character, 
    for (uint8_t i='!'; i<='z'; i++) 
    {
      alpha4.writeDigitAscii(0, i);
      alpha4.writeDigitAscii(1, i+1);
      alpha4.writeDigitAscii(2, i+2);
      alpha4.writeDigitAscii(3, i+3);
      alpha4.writeDisplay();

      delay(300);
    }    
}

void QuadAlphanumericWing::serialInput()
{
    Serial.println("Start typing to display!");    
    while (! Serial.available()) return;

    char c = Serial.read();
    if (! isprint(c)) return; // only printable!

    //TODO: implement the rest
}

void QuadAlphanumericWing::scrollingText()
{
    scrollingTextIndex++;
    
    if(scrollingTextIndex == scrollingTextLength)
    {
        scrollingTextIndex = 0;
    }
    
    char c = text[scrollingTextIndex];    
    
    // scroll down display
    displaybuffer[0] = displaybuffer[1];
    displaybuffer[1] = displaybuffer[2];
    displaybuffer[2] = displaybuffer[3];
    displaybuffer[3] = c;

    // set every digit to the buffer
    alpha4.writeDigitAscii(0, displaybuffer[0]);
    alpha4.writeDigitAscii(1, displaybuffer[1]);
    alpha4.writeDigitAscii(2, displaybuffer[2]);
    alpha4.writeDigitAscii(3, displaybuffer[3]);

    // update the display
    alpha4.writeDisplay();
}


void QuadAlphanumericWing::oneLoop()
{
    Serial.println("alpha quad loop");
 
    switch(wingMode)
    {
        case SERIAL_INPUT:
        {
            serialInput();
            
            break;
        }
        case SCROLLING_TEXT:
        {
            scrollingText();
            
            break;
        }
        default:
        {
            Serial.println("unknown mode " + wingMode);
        }
    }
}
