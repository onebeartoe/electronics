
#include <Arduino.h>

#include "Buzzer.h"

Buzzer::Buzzer()
{
    interval = 1000 * 10; // every ten seconds
}

void Buzzer::oneLoop()
{
    Serial.println("do nothing in Buzzer::oneLoop() ");   
}
