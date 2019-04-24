
// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN A0     // what pin we're connected to

#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);

// serial output interval configuration
unsigned long serialPreviousMillis = 0;
const long serialInterval = 5000; // five seconds

char * temperatureTopic = "rainmaker-workroom-2-temperature";

char * pressureTopic = "rainmaker-workroom-2-pressure";

void loop() 
{
    unsigned long currentMillis = millis();
    
    serialOutput(currentMillis);
}

void serialOutput(unsigned long currentMillis)
{
    if(currentMillis - serialPreviousMillis >= serialInterval) 
    {
        serialPreviousMillis = currentMillis;
        
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
            serialOutputSensorData(currentMillis, h, t);
        }
    }
}

void serialOutputSensorData(unsigned long currentMillis, float humidity, float temperature)
{
    Serial.print(currentMillis); 
    Serial.print("  : "); 
    Serial.print("Humidity : "); 
    Serial.print(humidity);
    Serial.println();

    Serial.print(currentMillis); 
    Serial.print("  : "); 
    Serial.print(temperatureTopic); 
    Serial.print("  : "); 
    Serial.print(temperature);
    Serial.print("  : "); 
    Serial.print(" C  ");
    Serial.println();
}

void setup() 
{
    Serial.begin(9600); 
    
    Serial.println("the weather station relay is setting up...");

    dht.begin();
    
    Serial.println("weather station setup complete");    
}
