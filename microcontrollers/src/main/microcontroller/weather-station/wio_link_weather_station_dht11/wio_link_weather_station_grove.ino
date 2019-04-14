
/**
 *   Temperature and Humidity Sensor
 *
 *       http://wiki.seeedstudio.com/Grove-Temperature_and_Humidity_Sensor_Pro/
 *
 *  
 *	https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11-p-745.html
 */

#include <AdafruitIO_WiFi.h>
#include <Adafruit_MCP9808.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

#include "configuration.h"

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN 2

#define DHTTYPE DHT11   // DHT 11


DHT dht(DHTPIN, DHTTYPE);

int photocell;

//Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

// These next two variables hold the values that are read from the sensors and sent
// to Adafruit IO MQTTP feeds.
float degreesCelsius;
int lightReading;

unsigned long previousMillis = 0;
const long interval = 1000 * 60;  // once a minute

const char* host = "www.adafruit.com";

// set up the Adafruit IO temperature feed
AdafruitIO_WiFi io(ADAFRUIT_USERNAME, AIO_KEY, wifi_ssid, wifi_password);
AdafruitIO_Feed *temperatureFeed = io.feed("rainmaker-backyard-bottom-temperature");
AdafruitIO_Feed *lightFeed = io.feed("rainmaker-backyard-bottom-light");
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

void lightSensor()
{
    long a0 = analogRead(A0);
    Serial.print("a0: ");
    Serial.println(a0);
    lightReading = a0;
}

void loop()
{
    unsigned long currentMillis = millis();
    
    if(currentMillis - previousMillis >= interval) 
    {
        previousMillis = currentMillis;
        
        lightSensor();

//        mcp9808Temp();
        
//        mqttpUpdate();
    }
    
    loopDht();
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

void mqttpSetup()
{
    // connect to io.adafruit.com
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

void mqttpUpdate()
{
  // The io.run() call is required to keep the client connection to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  // save the current state to the 'temperatureFeed' feed on adafruit io
  Serial.print("updating temperature via MQTTP with: ");
  Serial.println(degreesCelsius);
  temperatureFeed->save(degreesCelsius);
  
  lightFeed->save(lightReading);
}

void setup() 
{  
    Serial.begin(9600);
    
    wioLinkSetup();
    
    connectToWifiNetwork();
    
//    initializeMcp9808();
    
//    mqttpSetup();
    
    dthSetup();
}

void dthSetup()
{
        Serial.println("DHTxx test!");

    dht.begin();
}

void wioLinkSetup()
{
    // from the Seeed Studio Wio Link 'Advanced' guide,
    pinMode(15, OUTPUT);
//    digitalWrite(15, 0);  // gives 0 degrees reading
    digitalWrite(15, 1); // gives 32 degrees reading    
}