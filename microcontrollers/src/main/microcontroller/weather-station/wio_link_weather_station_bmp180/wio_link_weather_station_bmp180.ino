
/**
 *   Temperature and Humidity Sensor
 *
 *      https://www.adafruit.com/product/1603
 * 
 *      https://learn.adafruit.com/bmp085#wiring-the-bmp085
 */

#include <AdafruitIO_WiFi.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

#include "configuration.h"

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "Wire.h"
#include "Adafruit_BMP085.h"
 
Adafruit_BMP085 bmp;

// These next two variables hold the values that are read from the sensors and sent
// to Adafruit IO MQTTP feeds.
float degreesCelsius;
float pressureReading;

unsigned long previousMillis = 0;
const long interval = 1000 * 60;  // once a minute

//const char* host = "io.adafruit.com";
//const char* host = "www.adafruit.com";

// set up the Adafruit IO temperature feed
AdafruitIO_WiFi io(ADAFRUIT_USERNAME, AIO_KEY, wifi_ssid, wifi_password);
AdafruitIO_Feed *temperatureFeed = io.feed("rainmaker-backyard-top-temperature");
AdafruitIO_Feed *lightFeed = io.feed("rainmaker-backyard-top-pressure");

void connectToWifiNetwork()
{
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);
  
  WiFi.begin(wifi_ssid, wifi_password);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());    
}

void loop()
{
    unsigned long currentMillis = millis();
    
    if(currentMillis - previousMillis >= interval) 
    {
        previousMillis = currentMillis;
           
        degreesCelsius = bmp.readTemperature();
        Serial.print("Temperature = ");
        Serial.print(degreesCelsius);
        Serial.println(" *C");

        pressureReading = bmp.readPressure();
        Serial.print("Pressure = ");
        Serial.print(pressureReading);
        Serial.println(" Pa");

        Serial.println();
        
        mqttpUpdate();
    }
    
Serial.print("sure = ");
    
    delay(500);
}

void mqttpSetup()
{
    delay(2500);
      
      
    // connect to io.adafruit.com
    Serial.println();
    Serial.print("Connecting to Adafruit IO");
    io.connect();

    int c = 0;
    // wait for a connection
    while(io.status() < AIO_CONNECTED) 
    {
      Serial.print(".");
      delay(500);
      
      if(c % 50 == 0)
      {
         
         Serial.print("status: ");
         
         Serial.print( io.status() );
         Serial.println();
      }
      c++;
    }

    // we are connected
    Serial.println();
    Serial.println(io.statusText());    
}

void mqttpUpdate()
{
  // The io.run() call is required to keep the client connection to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  // save the current state to the 'temperatureFeed' feed on adafruit io
  Serial.print("updating temperature via MQTTP with: ");
  Serial.println(degreesCelsius);
  temperatureFeed->save(degreesCelsius);
  
  lightFeed->save(pressureReading);
}

void setup() 
{  
    Serial.begin(9600);
    
    Serial.print("sure = ");
    Serial.println("ploop");
    
    wioLinkSetup();
    
    connectToWifiNetwork();
    
    mqttpSetup();

    bmp.begin();  
}

void wioLinkSetup()
{
    // from the Seeed Studio Wio Link 'Advanced' guide,
    pinMode(15, OUTPUT);
//    digitalWrite(15, 0);  // gives 0 degrees reading
    digitalWrite(15, 1); // gives 32 degrees reading    
}
