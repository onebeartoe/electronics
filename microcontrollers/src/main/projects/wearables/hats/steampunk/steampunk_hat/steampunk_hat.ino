
#include <Arduino.h>

#include "Mister.h"

#include "Gear.h"

/*
  Fade

  This example shows how to fade the onboard Raspberry Pi Pico LED

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Fade
*/

int led = LED_BUILTIN; // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
const int GEAR_BUTTON_PIN = 21;

Mister mister;

Gear gear;

// the setup routine runs once when you press reset:
void setup()
{
  // declare pin to be an output:
  pinMode(led, OUTPUT);

  // set up button pin with internal pull-up and attach ISR on button release (RISING edge)
  pinMode(GEAR_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(GEAR_BUTTON_PIN), activateGear, FALLING);

  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() 
{

  // set the brightness
  analogWrite(led, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) 
  {
    fadeAmount = -fadeAmount;
  }

//TODO: refactor this to use timing variables
  // wait for 30 milliseconds to see the dimming effect
  delay(30);

  mister.loop();

  gear.loop();
}

void activateGear() 
{
  Serial.println("Activating gear...");

  gear.oneLoop();

  Serial.println("... deactivating gear");
}