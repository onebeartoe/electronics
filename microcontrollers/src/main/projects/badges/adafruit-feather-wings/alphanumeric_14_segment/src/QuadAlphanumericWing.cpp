
#include "Adafruit_LEDBackpack.h"

#include "QuadAlphanumericWing.h"

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();



int scrollingTextIndex;

bool debug = false;

QuadAlphanumericWing::QuadAlphanumericWing()
{
    const char * text = scrollingText.c_str();
    
    scrollingTextLength = strlen(text);
    
    interval = 350;
    
    wingMode = SCROLLING_TEXT;
    
    alpha4.begin(0x70);  // pass in the address
    
    alpha4.setBrightness(6);

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

void QuadAlphanumericWing::oneLoop()
{
    if(debug)
    {
        //TODO: move to a proper logger with levels
        
        Serial.println("alpha quad loop");
    }

    switch(wingMode)
    {
        case SERIAL_INPUT:
        {
            serialInput();
            
            break;
        }
        case SCROLLING_TEXT:
        {
            scrollText();
            
            break;
        }
        case STILL:
        {
            // do nothing
            
            break;
        }
        default:
        {
            Serial.println("unknown mode " + wingMode);
        }
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

void QuadAlphanumericWing::setText(String text)
{    
    char char1 = ' ';
    char char2 = ' ';
    char char3 = ' ';
    char char4 = ' ';
    
    if(text.length() > 0)
    {
        char1 = text.charAt(0);
    }
    
    if(text.length() > 1)
    {
        char2 = text.charAt(1);
    }
    
    if(text.length() > 2)
    {
        char3 = text.charAt(2);
    }
    
    if(text.length() > 3)
    {
        char4 = text.charAt(3);
    }
    
    alpha4.writeDigitAscii(0, char1);
    alpha4.writeDigitAscii(1, char2);
    alpha4.writeDigitAscii(2, char3);
    alpha4.writeDigitAscii(3, char4);
    
    alpha4.writeDisplay();    
}

void QuadAlphanumericWing::setScrollingText(String text)
{
    this->scrollingTextLength = strlen(text.c_str() );
    
    this->scrollingText = text;
}

void QuadAlphanumericWing::setWingMode(WingMode mode)
{
    this->wingMode = mode;
}

void QuadAlphanumericWing::scrollText()
{
    scrollingTextIndex++;
    
    if(scrollingTextIndex == scrollingTextLength)
    {
        scrollingTextIndex = 0;
    }
    
    const char * text = scrollingText.c_str();
    
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
