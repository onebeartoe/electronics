
#include <AdafruitIO_WiFi.h>
#include <Adafruit_MCP9808.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

#include "configuration.h"

// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

float degreesCelsius;

//int ledState = LOW;     

unsigned long previousMillis = 0;
const long interval = 2500;

const char* host = "www.adafruit.com";

// set up the Adafruit IO temperature feed
AdafruitIO_WiFi io(ADAFRUIT_USERNAME, AIO_KEY, wifi_ssid, wifi_password);
AdafruitIO_Feed *digital = io.feed("rainmaker-backyard-bottom-temperature");

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

void httpRequest()
{
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) 
  {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/testwifi/index.html";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available())
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");    
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

void loop()
{
    unsigned long currentMillis = millis();
    
    if(currentMillis - previousMillis >= interval) 
    {
        // this is for the light sensor
        long a0 = analogRead(A0);
        Serial.print("a0: ");
        Serial.println(a0);
    
        previousMillis = currentMillis;

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
//TODO: do we really need the next call to delay?    
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

  // save the current state to the 'digital' feed on adafruit io
  Serial.print("updating via MQTTP with: ");
  Serial.println(degreesCelsius);
  digital->save(degreesCelsius);    
}

void setup() 
{
    pinMode(LED_BUILTIN, OUTPUT);
  
    // from the Seeed Studio Wio Link 'Advanced' guide,
    pinMode(15, OUTPUT);
//    digitalWrite(15, 0);  // gives 0 degrees reading
    digitalWrite(15, 1); // gives 32 degrees reading
  
    Serial.begin(9600);
    
    connectToWifiNetwork();
    
    initializeMcp9808();
    
    mqttpSetup();
}
