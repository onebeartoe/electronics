
#include <Arduino.h>

#include "Gear.h"

Gear::Gear()
{
    interval = 1000 * 10; // every ten seconds
}

void Gear::oneLoop()
{
    Serial.println("do nothing in Gear::oneLoop() ");   
}
