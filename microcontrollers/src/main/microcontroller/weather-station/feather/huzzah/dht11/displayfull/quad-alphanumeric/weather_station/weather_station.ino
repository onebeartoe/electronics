
#include "DHT.h"

/**
 *   Temperature and Humidity Sensor
 *
 *       http://wiki.seeedstudio.com/Grove-Temperature_and_Humidity_Sensor_Pro/
 *
 *  
 *	https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11-p-745.html
 */

// this next library is only used to turn off Wifi on the Huzzah.
#include <ESP8266WiFi.h>

#define DHTPIN 2

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

float degreesCelsius;

unsigned long previousMillis = 0;

//const long interval = 1000 * 60;  // once a minute
const long interval = 1000 * 5;  // once every 5 seconds

void loop()
{
    unsigned long currentMillis = millis();
    
    if(currentMillis - previousMillis >= interval) 
    {
        previousMillis = currentMillis;
        
        loopDht();
    }
}

void loopDht()
{
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    // check if returns are valid, if they are NaN (not a number) then something went wrong!
    if (isnan(t) || isnan(h)) 
    {
        Serial.println("Failed to read from DHT");
    } 
    else 
    {
        Serial.print("Humidity: "); 
        Serial.print(h);
        Serial.print(" %\t");
        Serial.print("Temperature: "); 
        Serial.print(t);
        Serial.println(" *C");
    }
}

void setup() 
{  
    Serial.begin(9600);

    Serial.println("Application setup is in progress.");

    // this version does not use Wifi at all.
    WiFi.mode(WIFI_OFF);
        
    dthSetup();
}

void dthSetup()
{
    dht.begin();
    
    Serial.println("DHT1 is setup.");
}
