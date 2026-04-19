
#include <Arduino.h>

#include "Mister.h"

Mister::Mister()
{
    interval = 1000 * 5; // every five seconds
}

void Mister::oneLoop()
{
    Serial.println("do nothing in Mister::oneLoop() ");   
}
