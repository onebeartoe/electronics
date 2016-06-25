
/**
 * This code was originally from these two sources:
 *  
 *    https://learn.adafruit.com/i31fl3731-16x9-charliplexed-pwm-led-driver?view=all
 *    
 *    https://www.arduino.cc/en/Tutorial/DueSimpleWaveformGenerator
 */

/*
  Simple Waveform generator with Arduino Due

  * connect two push buttons to the digital pins 2 and 3 
    with a 10 kilohm pulldown resistor to choose the waveform
    to send to the DAC0 and DAC1 channels
  * connect a 10 kilohm potentiometer to A0 to control the 
    signal frequency

 */

#include "Waveforms.h"

#include <Wire.h>

#include "beto_Adafruit_IS31FL3731.h"

Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();

#define oneHzSample 1000000/maxSamplesNum  // sample for the 1Hz signal expressed in microseconds 

const int button0 = 2, button1 = 3;
volatile int wave0 = 0, wave1 = 0;

int i = 0;
int sample;


void setup() 
{
  pinMode(A0, OUTPUT);
//  analogWriteResolution(12);  // set the analog output resolution to 12 bit (4096 levels)
//  analogReadResolution(12);   // set the analog input resolution to 12 bit 

//  attachInterrupt(button0, wave0Select, RISING);  // Interrupt attached to the button connected to pin 2
//  attachInterrupt(button1, wave1Select, RISING);  // Interrupt attached to the button connected to pin 3


  if (! matrix.begin()) {
  //  Serial.println("IS31 not found");
    while (1);
  }

  matrix.audioSync(true);
}

void loop() {
  // Read the the potentiometer and map the value  between the maximum and the minimum sample available
  // 1 Hz is the minimum freq for the complete wave
  // 170 Hz is the maximum freq for the complete wave. Measured considering the loop and the analogRead() time
  sample = map(analogRead(A0), 0, 4095, 0, oneHzSample);
  sample = constrain(sample, 0, oneHzSample);

  analogWrite(A0, waveformsTable[wave0][i]);  // write the selected waveform on DAC0
//  analogWrite(DAC0, waveformsTable[wave0][i]);  // write the selected waveform on DAC0
//  analogWrite(DAC1, waveformsTable[wave1][i]);  // write the selected waveform on DAC1


 // audio mode
  matrix.writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_CONFIG, ISSI_REG_CONFIG_AUDIOPLAYMODE);
  matrix.audioSync(true);

  i++;
  if(i == maxSamplesNum)  // Reset the counter to repeat the wave
    i = 0;

  delayMicroseconds(sample);  // Hold the sample value for the sample time
}

// function hooked to the interrupt on digital pin 2
void wave0Select() {
  wave0++;
  if(wave0 == 4)
    wave0 = 0;
}

// function hooked to the interrupt on digital pin 3
void wave1Select() {
  wave1++;
  if(wave1 == 4)
    wave1 = 0;
}

