

//TODO: add the Web code from here:
//          https://github.com/onebeartoe/electronics/blob/master/microcontrollers/src/main/microcontroller/weather-station/feather/huzzah/bmp180/headless/huzzah_feather_weather_station_bmp180/huzzah_feather_weather_station_bmp180.ino

/**
 * This file has WiFi configuration.
 */
#include "configuration.h"

#include "DHT.h"

/**
 *   Temperature and Humidity Sensor
 *
 *      http://wiki.seeedstudio.com/Grove-Temperature_and_Humidity_Sensor_Pro/
 *
 *  
 *	    https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11-p-745.html
 *
 *   Quadalpha Numeric FeatherWing Display
 *
 *      https://www.adafruit.com/product/3129
 */

#include "AdafruitIO_WiFi.h"

AdafruitIO_WiFi io(ADAFRUIT_USERNAME, AIO_KEY, wifi_ssid, wifi_password);

// set up the 'temperature' and 'humidity' feeds
AdafruitIO_Feed *temperature = io.feed("rainmaker-backyard-top-temperature");
AdafruitIO_Feed *humidity = io.feed("rainmaker-backyard-top-pressure");

#include "relative-path-includes.h"

AdafruitIoTask ioTask;
//AdafruitIoTask ioTask();

#define DHTPIN 2

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

float degreesCelsius;

unsigned long previousMillis = 0;

//const long interval = 1000 * 60;  // once a minute
const long interval = 1000 * 5;  // once every 5 seconds

QuadAlphanumericWing alphaWing;

boolean tempOrHumidityToggle = false; // if this value is true then display the temperature, otherwise then display the humidity

void dthSetup()
{
    dht.begin();
    
    Serial.println("DHT1 is setup.");
}

void loop()
{
    unsigned long currentMillis = millis();
    
    if(currentMillis - previousMillis >= interval) 
    {
        previousMillis = currentMillis;
        
        loopDht();
    }

    ioTask.loop();
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
     
// to Fahrenheit
//  Fahrenheit = ((9 * Centigrade) / 5.0) + 32        
        
        float f = ((9 * t) / 5.0) + 32;
        
        int fahrenheitAsInt = (int) f;
        
        String s;
        
        if(tempOrHumidityToggle)
        {
            s = padInt("T", fahrenheitAsInt);
        }
        else
        {
            int humidityAsInt = (int) h;        
            
            s = padInt("H", humidityAsInt);
        }
        
        alphaWing.setText(s);
        
        Serial.print("toggle: ");
        Serial.println(tempOrHumidityToggle);
        
        // toggle the display mode
        tempOrHumidityToggle = !tempOrHumidityToggle;
    }
}

String padInt(String prefix, int i)
{
    String paddedString = "";
    
    if(i < 10)
    {
        // pad two spaces
        paddedString += "  "; 
    }
    else if(i < 99)
    {
        // pad one space
        paddedString += " ";
    }
    
    return prefix + paddedString + String(i);
}

void setup() 
{  
    Serial.begin(9600);

    Serial.println("Application setup is in progress.");


        
    dthSetup();
    
//    alphaWing.brightness(5);
    alphaWing.setWingMode(TextWingModes::STILL);    
}
