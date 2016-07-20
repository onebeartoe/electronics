
/**
 * This source works with the following products:
 * 
 *      Adafruit 16x9 Charlieplexed PWM LED Matrix Driver - IS31FL3731
 *      https://www.adafruit.com/products/2946
 * 
 *      LED Charlieplexed Matrix - 9x16 LEDs - Green
 *      https://www.adafruit.com/products/2972
 * 
 * Use 'USBtinyISP' as the programmer.
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

Adafruit_IS31FL3731_Wing matrix = Adafruit_IS31FL3731_Wing();

void setup() {

  Serial.begin(9600);
  Serial.println("ISSI manual animation test");
  if (! matrix.begin()) 
  {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 Found!");

  matrix.setRotation(0);
  matrix.setCursor(0,0);
  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(100);  
}

void loop() 
{

  for (int8_t x=0;
            x>=-200;
//            x>=-100;  // too short
//            x>=-300;  // too long
//            x>=-400;
//          x>=-500;
//          x>=-550;
//        x>=-600;
//        x>=-632; 
        x--) 
  {
    matrix.clear();
    matrix.setCursor(x,1);
    matrix.print("Hello, my name is Roberto!");
    delay(100);
  }
}
