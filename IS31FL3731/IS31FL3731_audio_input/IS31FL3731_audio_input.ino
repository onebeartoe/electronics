
/**
 * This example uses these products:
 * 
 *    Adafruit 16x9 Charlieplexed PWM LED Matrix Driver - IS31FL3731
 *    https://www.adafruit.com/products/2946
 *    
 *    LED Charlieplexed Matrix - 9x16 LEDs - Green
 *    https://www.adafruit.com/products/2972
 * 
 *    Adafruit Pro Trinket - 5V 16MHz
 *    https://www.adafruit.com/product/2000
 *    
 *    Electret Microphone Amplifier - MAX9814 with Auto Gain Control
 *    https://www.adafruit.com/products/1713
 *    
 * Here is a tutorial on the LED matrix and driver:
 *  
 *    https://learn.adafruit.com/i31fl3731-16x9-charliplexed-pwm-led-driver?view=all
 *    
 */

#include <Wire.h>

//#include <Adafruit_IS31FL3731.h>
#include "beto_Adafruit_IS31FL3731.h"

Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();

void setup() 
{
  pinMode(A0, OUTPUT);

  if (! matrix.begin()) 
  {
    // the IS31 has not been found yet
    while (1);
  }
  
  // This next method was moved from the protected to public section of the method declartions in the .h file.
  matrix.writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_CONFIG, ISSI_REG_CONFIG_AUDIOPLAYMODE);
  matrix.audioSync(true);
}

void loop() 
{
  // the main loop does nothing
  delay(500);
}

