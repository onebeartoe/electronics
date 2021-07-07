
#include <AdafruitIO_WiFi.h>
#include <Adafruit_MCP9808.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

#include "configuration.h"

int photocell;

Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

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

void initializeMcp9808()
{
    // Make sure the sensor is found, you can also pass in a different i2c
  // address with tempsensor.begin(0x19) for example
  if (!tempsensor.begin()) 
  {
    Serial.println("Couldn't find MCP9808!");
    while (1);
  }
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

        mcp9808Temp();
        
        mqttpUpdate();
    }
}

void mcp9808Temp()
{
    // Read and print out the temperature, then convert to *F
    degreesCelsius = tempsensor.readTempC();
    float f = degreesCelsius * 9.0 / 5.0 + 32;
    Serial.print("\nTemperature: "); Serial.print(degreesCelsius); Serial.print("*C\t\t\t"); 
    Serial.print(f); Serial.println("*F"); 
    delay(250);

//    Serial.println("Shutdown MCP9808.... ");
    tempsensor.shutdown_wake(1); // shutdown MSP9808 - power consumption ~0.1 mikro Ampere

    delay(2000);

//    Serial.println("wake up MCP9808.... "); // wake up MSP9808 - power consumption ~200 mikro Ampere
    tempsensor.shutdown_wake(0);    
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
    
    Serial.println("The weather station is booting.");
    
    wioLinkSetup();
    
    connectToWifiNetwork();
    
    initializeMcp9808();
    
    mqttpSetup();
}

void wioLinkSetup()
{
    // from the Seeed Studio Wio Link 'Advanced' guide,
    pinMode(15, OUTPUT);
//    digitalWrite(15, 0);  // gives 0 degrees reading
    digitalWrite(15, 1); // gives 32 degrees reading    
}
