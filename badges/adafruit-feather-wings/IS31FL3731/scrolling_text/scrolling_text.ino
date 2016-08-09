
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
  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(100);  
}

int iterationLimit = -200;
//                 = -100;  // too short
//                 = -300;  // too long

//String message = "Hola me llamo Roberto";
String message = "Bueno, my name is Roberto!";

void loop() 
{
  for (int8_t x=0; x>=iterationLimit; x--) 
  {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print(message);
    delay(100);
  }
}
