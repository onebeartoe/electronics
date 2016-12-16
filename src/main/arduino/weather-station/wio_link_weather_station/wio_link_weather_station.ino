
#include "DHT.h"   //  https://github.com/adafruit/DHT-sensor-library
#include <ESP8266WiFi.h>

// The following two (commented) char pointers are stored in a file that is not
// committed to the source code repository for security.
#include "C:\home\owner\workspace\info.h"
//const char* ssid     = "wifi-access-point-ssid";
//const char* password = "!!!CORRECT-ME!!!";

/* 
 ESP8266 BlinkWithoutDelay by Simon Peter
 Blink the blue LED on the ESP-01 module
 Based on the Arduino Blink without Delay example
 This example code is in the public domain
 
 The blue LED on the ESP-01 module is connected to GPIO1 
 (which is also the TXD pin; so we cannot use Serial.print() at the same time)
 
 Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/


// digital pins
#define DHTPIN 14     // temperature and humidity sensor pin 

#define DHTTYPE DHT11    // sensor type: http://www.seeedstudio.com/depot/Grove-TempHumi-Sensor-p-745.html
DHT htSensor(DHTPIN, DHTTYPE);
float humidity;
float internalCelsiusTemperature;
float internalFahrenheitTemperature;

int ledState = LOW;     

unsigned long previousMillis = 0;
const long interval = 2500;

const char* host = "www.google.com";

void connectToWifiNetwork()
{
    connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
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

void humidityTemperatureSensor()
{
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    humidity = htSensor.readHumidity();
    internalCelsiusTemperature = htSensor.readTemperature();
    internalFahrenheitTemperature  = internalCelsiusTemperature * 9 / 5 + 32;
  
    Serial.println();
    Serial.print(internalCelsiusTemperature);
    Serial.print("C - ");
    
    Serial.print(internalFahrenheitTemperature);
    Serial.println("F");  
}

void loop()
{
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= interval) 
    {
        long a0 = analogRead(A0);
        Serial.print("a0: ");
        Serial.println(a0);
    
        previousMillis = currentMillis;   

        if (ledState == LOW)
          ledState = HIGH;  // Note that this switches the LED *off*
        else
          ledState = LOW;   // Note that this switches the LED *on*
        digitalWrite(LED_BUILTIN, ledState);

        humidityTemperatureSensor();
        
        httpRequest();
    }
}

void setup() 
{
    pinMode(LED_BUILTIN, OUTPUT);
  
    // from the 'Advanced' page
    pinMode(15, OUTPUT);
//    digitalWrite(15, 0);
    digitalWrite(15, 1);
  
    Serial.begin(9600);
  
    htSensor.begin();
    
    Serial.print("built-in LED pin: ");
    Serial.println(LED_BUILTIN);
    
    connectToWifiNetwork();
}
