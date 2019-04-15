// this really didn't work with the Wio Link'

// Adafruit IO Temperature & Humidity Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-temperature-and-humidity
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016-2017 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "configuration.h"



/************************ Example Starts Here *******************************/


#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(ADAFRUIT_USERNAME, AIO_KEY, wifi_ssid, wifi_password);

//#include <Adafruit_Sensor.h>
//#include <DHT.h>
//#include <DHT_U.h>

// pin connected to DH22 data line
//#define DATA_PIN 2

#include "Adafruit_BMP085.h"
 
Adafruit_BMP085 bmp;

// These next two variables hold the values that are read from the sensors and sent
// to Adafruit IO MQTTP feeds.
float degreesCelsius;
float pressureReading;

// create DHT22 instance
//DHT_Unified dht(DATA_PIN, DHT22);

// set up the 'temperature' and 'humidity' feeds
AdafruitIO_Feed *temperature = io.feed("rainmaker-backyard-top-temperature");
AdafruitIO_Feed *humidity = io.feed("rainmaker-backyard-top-pressure");

unsigned long previousMillis = 0;
const long interval = 1000 * 60;  // once a minute

void setup() 
{

  // start the serial connection
  Serial.begin(9600);

    // wait for serial monitor to open
    while(! Serial);

    // initialize the temperature and pressure sensor
    bmp.begin();

    // connect to io.adafruit.com

    Serial.println("\n\n");
    Serial.println("\n\n");  
    Serial.print("Connecting to Adafruit IO");
    io.connect();

    // wait for a connection
    while(io.status() < AIO_CONNECTED) 
    {
      Serial.print(".");
      delay(500);
    }

    // we are connected
    Serial.println();
    Serial.println(io.statusText());
}

void loop() 
{
    io.run();

        degreesCelsius = bmp.readTemperature();
        Serial.print("Temperature = ");
        Serial.print(degreesCelsius);
        Serial.println(" *C");

        pressureReading = bmp.readPressure();
        Serial.print("Pressure = ");
        Serial.print(pressureReading);
        Serial.println(" Pa");

        Serial.println();
  

    unsigned long currentMillis = millis();
    
    if(currentMillis - previousMillis >= interval) 
    {
        previousMillis = currentMillis;
           


  // save fahrenheit (or celsius) to Adafruit IO
  temperature->save(degreesCelsius);



  Serial.println("posting to Adafruit Io");

  // save humidity to Adafruit IO
  humidity->save(pressureReading);
        
        
    }  
  
  // wait 5 seconds (5000 milliseconds == 5 seconds)
  delay(5000);

}
