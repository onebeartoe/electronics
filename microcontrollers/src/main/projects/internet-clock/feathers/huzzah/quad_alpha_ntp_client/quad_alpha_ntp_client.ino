
#include <ESP8266WiFi.h>

// the Wifi credentials are stored in this file:
#include "/home/roberto/Workspace/owner/arduino/secret.h"

#include "relative-path-includes.h"

#include "DisplayUpdater.h"

InternetClock clock;

QuadAlphanumericWing alphaWing;

DisplayUpdater displayUpdater(&clock, &alphaWing);

void setup()
{
    Serial.begin(115200);

    WiFi.begin(wifi_ssid, wifi_password);

    while ( WiFi.status() != WL_CONNECTED ) 
    {
        delay ( 500 );
        Serial.print ( "." );
    }
    
// the brightess is still set in QuadAlphanumericWing.cpp    
//    alphaWing.brightness(5);
    alphaWing.setWingMode(WingMode::STILL);
    
    clock.interval = 5 * 1000; // every 2 seconds
}

void loop() 
{
    clock.loop();
    
    alphaWing.loop();
    
    displayUpdater.loop();
}
