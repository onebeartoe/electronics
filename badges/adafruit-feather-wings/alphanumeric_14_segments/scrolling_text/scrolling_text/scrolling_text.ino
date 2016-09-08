
/**
  * Lovely
  */

// Demo the quad alphanumeric display LED backpack kit
// scrolls through every character, then scrolls Serial
// input onto the display

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

#include "scrolling_text.h"

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

/**
 * This is the delay in milliseconds for the scrolling text.
 */
long scrollDelay = 350;

void setup() 
{
    w = 3;
    
    Serial.begin(9600);
  
    // pass in the address
    alpha4.begin(0x70);  

  
    alpha4.clear();
    alpha4.writeDisplay();
   
    Serial.println("The Adafruit_AlphaNum4 setup is complete.");
}

String message = "  Go Spurs Go   *   Timmy Rules!   * Burce Bruce   *";

int messageLength = message.length();

/**
  * This array holds the current values of the 4 alphanumeric segments.
  */
char displaybuffer[] = {' ', ' ', ' ', ' '};

int indecies[] = {0,1,2,3};

unsigned long lightPreviousMillis = 0;

unsigned long currentMillis;

void loop() 
{
    currentMillis = millis();
    
    if(currentMillis - lightPreviousMillis >= scrollDelay) 
    {
        // save the last time you blinked the LED
        lightPreviousMillis = currentMillis;

        updateDisplay();
    } 
}

void updateDisplay()
{
    // shift the index into the message for each segment 
    indecies[0] += 1;
    indecies[1] += 1;
    indecies[2] += 1;
    indecies[3] += 1;

    if(indecies[0] == messageLength)
    {
        indecies[0] = 0;
    }

    if(indecies[1] == messageLength)
    {
        indecies[1] = 0;
    }

    if(indecies[2] == messageLength)
    {
        indecies[2] = 0;
    }

    if(indecies[3] == messageLength)
    {
        indecies[3] = 0;
    }
  
  // scroll down display
  displaybuffer[0] = message[indecies[0]];
  displaybuffer[1] = message[indecies[1]];
  displaybuffer[2] = message[indecies[2]];
  displaybuffer[3] = message[indecies[3]];
 
  // set every digit to the buffer
  alpha4.writeDigitAscii(0, displaybuffer[0]);
  alpha4.writeDigitAscii(1, displaybuffer[1]);
  alpha4.writeDigitAscii(2, displaybuffer[2]);
  alpha4.writeDigitAscii(3, displaybuffer[3]);
 
  // write it out!
  alpha4.writeDisplay();    
}