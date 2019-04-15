
// display: 
//      https://www.adafruit.com/product/3150
//
//      https://learn.adafruit.com/adafruit-8x16-led-matrix-featherwing/overview

// temperature and humidity sensor
//
//      https://www.adafruit.com/product/1603

#include "configuration.h"

#include "AdafruitIO_WiFi.h"
#include "Adafruit_BMP085.h"
#include "Adafruit_LEDBackpack.h"

#include <Adafruit_GFX.h>
#include <Wire.h>

AdafruitIO_WiFi io(ADAFRUIT_USERNAME, AIO_KEY, wifi_ssid, wifi_password);
 
Adafruit_BMP085 bmp;

float degreesCelsius;

float pressureReading;

// set up the Adafruit IO 'temperature' and 'humidity' feeds
AdafruitIO_Feed *temperature = io.feed("rainmaker-backyard-top-temperature");
AdafruitIO_Feed *humidity = io.feed("rainmaker-backyard-top-pressure");

// AIO post interval settings
unsigned long aioPostPreviousMillis = 0;
const long aioPostInterval = 1000 * 60;  // once a minute

// serial ouput interval settings
unsigned long serialPreviousMillis = 0;
const long serialInterval = 5000; // five seconds

Adafruit_8x16minimatrix matrix = Adafruit_8x16minimatrix();

void aioPost(unsigned long currentMillis)
{
    if(currentMillis - aioPostPreviousMillis >= aioPostInterval) 
    {
        aioPostPreviousMillis = currentMillis;

        // save fahrenheit (or celsius) to Adafruit IO
        temperature->save(degreesCelsius);

        Serial.println("posting to Adafruit IO");
        Serial.println();

        // save humidity to Adafruit IO
        humidity->save(pressureReading);
    }    
}

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
    
    matrix.begin(0x70);  // pass in the address
}

void loop() 
{
    io.run();
  
    unsigned long currentMillis = millis();

    serialOutput(currentMillis);
    
    aioPost(currentMillis);
}

void serialOutput(unsigned long currentMillis)
{
    if(currentMillis - serialPreviousMillis >= serialInterval) 
    {
        serialPreviousMillis = currentMillis;
        
        degreesCelsius = bmp.readTemperature();
        Serial.print("Temperature = ");
        Serial.print(degreesCelsius);
        Serial.println(" *C");

        pressureReading = bmp.readPressure();
        Serial.print("Pressure = ");
        Serial.print(pressureReading);
        Serial.println(" Pa");
        Serial.println();    
    }
}
