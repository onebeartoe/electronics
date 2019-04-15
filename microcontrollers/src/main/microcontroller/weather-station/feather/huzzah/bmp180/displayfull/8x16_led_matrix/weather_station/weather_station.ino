
#include "configuration.h"

#include "AdafruitIO_WiFi.h"
#include "Adafruit_BMP085.h"

AdafruitIO_WiFi io(ADAFRUIT_USERNAME, AIO_KEY, wifi_ssid, wifi_password);
 
Adafruit_BMP085 bmp;

float degreesCelsius;

float pressureReading;

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

        Serial.println();
        Serial.println("posting to Adafruit IO");

        // save humidity to Adafruit IO
        humidity->save(pressureReading);
    }  
  
    // wait 5 seconds (5000 milliseconds == 5 seconds)
    delay(5000);
}
