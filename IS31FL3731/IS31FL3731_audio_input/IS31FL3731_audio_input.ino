
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

#include "Waveforms.h"

#include <Wire.h>

#include "beto_Adafruit_IS31FL3731.h"

Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();

#define oneHzSample 1000000/maxSamplesNum  // sample for the 1Hz signal expressed in microseconds 

const int button0 = 2, button1 = 3;
volatile int wave0 = 0, wave1 = 0;


int sample;


void setup() 
{
  pinMode(A0, OUTPUT);

  if (! matrix.begin()) 
  {
  //  Serial.println("IS31 not found");
    while (1);
  }

  matrix.audioSync(true);
}

void loop() 
{
  // Read the the potentiometer and map the value  between the maximum and the minimum sample available
  // 1 Hz is the minimum freq for the complete wave
  // 170 Hz is the maximum freq for the complete wave. Measured considering the loop and the analogRead() time
  sample = map(analogRead(A0), 0, 4095, 0, oneHzSample);
  sample = constrain(sample, 0, oneHzSample);



 // audio mode
  matrix.writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_CONFIG, ISSI_REG_CONFIG_AUDIOPLAYMODE);
  matrix.audioSync(true);



  delayMicroseconds(sample);  // Hold the sample value for the sample time
}
