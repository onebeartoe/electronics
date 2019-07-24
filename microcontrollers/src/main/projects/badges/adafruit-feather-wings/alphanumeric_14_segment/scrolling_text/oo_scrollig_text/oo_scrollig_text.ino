
#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/badges/adafruit-feather-wings/alphanumeric_14_segment/src/relative-path-includes.h"

QuadAlphanumericWing alphaWing;

void setup() 
{
    Serial.begin(9600);

    Serial.println("oo scrollig text ready!");

    alphaWing.demo();

    Serial.println("oo scrollig text ready!");
}

void loop() 
{
    alphaWing.loop();
}
