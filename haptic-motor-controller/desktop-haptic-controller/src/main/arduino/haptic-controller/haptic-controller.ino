
// String split() -> http://stackoverflow.com/questions/11915914/splitting-a-comma-delimited-string-of-integers

// Adafruit Haptic Controller -> https://learn.adafruit.com/adafruit-drv2605-haptic-controller-breakout?view=all

#include <Wire.h>
#include "Adafruit_DRV2605.h"

#include "parseInts.h"

Adafruit_DRV2605 drv;

uint8_t effect = 1;

// 12 is the maximum length of a decimal representation of a 32-bit integer,
// including space for a leading minus sign and terminating null byte
char intBuffer[12];
String intData = "";
int delimiter = (int) '\n';

void setup() 
{
  Serial.begin(9600);
  Serial.println("DRV test");
  drv.begin();
  
  drv.selectLibrary(1);
  
  // I2C trigger by sending 'go' command 
  // default, internal trigger when sending GO command
  drv.setMode(DRV2605_MODE_INTTRIG); 
}

void readAndPlayEffect();

void loop() 
{  
  readAndPlayEffect();

  // wait a bit
  delay(500);
}

/**
 * reads a string of characters terminated by the delimiter character ('\n') from Serial input.
 */
void readAndPlayEffect() 
{
    while (Serial.available()) 
    {
        int ch = Serial.read();
        if (ch == -1) {
            // Handle error
        }
        else if (ch == delimiter) {
            break;
        }
        else {
            intData += (char) ch;
        }
    }

    if(intData.length() != 0)
    {
      // Copy read data into a char array for use by atoi
      // Include room for the null terminator
      int intLength = intData.length() + 1;
      intData.toCharArray(intBuffer, intLength);
  
      parseInts(intData);
  
      if(parseIntsArrayLength > 0)
      {
        Serial.print("parse ints length: "); Serial.print(parseIntsArrayLength);
        Serial.print(" - IDs: ");
        
        for(int i=0; i<parseIntsArrayLength; i++)
        {
          // set the effect to play
          int effect = parseIntsArray[i];

          Serial.print(effect); Serial.print(" ");
          
          drv.setWaveform(i, effect);  // play effect 
        }
        Serial.println();
        
        drv.setWaveform(parseIntsArrayLength, 0);       // end waveform
      
        // play the effect!
        drv.go();          
      }
    }
    
    // Reinitialize intData for use next time around the loop
    intData = "";    
}
