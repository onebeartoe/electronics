
/**
 * This is from JohnnyDoe's comment on this guide:
 * 
 *      https://www.hackster.io/rayburne/nist-date-time-with-esp8266-e8b9a9
 */
#include <ESP8266WiFi.h>

// the Wifi credentials are stored in this file:
#include "/home/roberto/Workspace/owner/arduino/secret.h"

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/relative-path-includes.h"

InternetClock clock;

void setup()
{
    Serial.begin(115200);

    WiFi.begin(wifi_ssid, wifi_password);

    while ( WiFi.status() != WL_CONNECTED ) 
    {
        delay ( 500 );
        Serial.print ( "." );
    }
}

void loop() 
{
    clock.loop();
}
