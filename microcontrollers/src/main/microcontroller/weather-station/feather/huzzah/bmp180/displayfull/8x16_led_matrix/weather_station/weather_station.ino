
// it is this one, for mom's weather station!

// LED matrix display: 
//
//      https://www.adafruit.com/product/3150
//
//      https://learn.adafruit.com/adafruit-8x16-led-matrix-featherwing/overview
//
// temperature and humidity sensor
//
//      https://www.adafruit.com/product/1603

#include "configuration.h"

#include "Adafruit_BMP085.h"

#include "Adafruit_LEDBackpack.h"

#include <Adafruit_GFX.h>
 
Adafruit_BMP085 bmp;

float degreesCelsius;

float degreesFahrenheit;

float pressureReading;

// serial output interval settings
unsigned long serialPreviousMillis = 0;
const long serialInterval = 5000; // five seconds

// LED display interval settings
unsigned long ledDisplayPreviousMillis = 0;
const long ledDisplayInterval = 500;  // one tenth of a second

Adafruit_8x16minimatrix matrix = Adafruit_8x16minimatrix();

// these next three hold values for the text scrolling
int8_t x=7;

int8_t xStart = 7;

int8_t xMin = -46;

String scrollText = "--temp";

char scrollTextBuffer[20] = "";

void ledDisplay(unsigned long currentMillis)
{
    if(currentMillis - ledDisplayPreviousMillis >= ledDisplayInterval) 
    {
        ledDisplayPreviousMillis = currentMillis;

        matrix.clear();
        matrix.setCursor(x,0);
        matrix.print(scrollText);
//        matrix.print("World");
        matrix.writeDisplay();
        
        x--;
        
        if(x == xMin)
        {
            x = xStart;
        }

        sensorReading();
    }
}

void sensorReading()
{
    // update the scrolling text
    int width = 8;
    int percision = 1;

    double degrees = degreesCelsius;

    bool FAHRENHEIT = true;

    if(FAHRENHEIT)
    {
        degreesFahrenheit = (9.0/5.0)*degreesCelsius + 32;

        degrees = degreesFahrenheit;
    }

    scrollText = dtostrf(degrees, width, percision, scrollTextBuffer);

    if(FAHRENHEIT)
    {
        scrollText += " F";
    }
    else
    {
        scrollText += " C";
    }    
}

void loop() 
{  
    unsigned long currentMillis = millis();

    serialOutput(currentMillis);
        
    ledDisplay(currentMillis);
}


void serialOutput(unsigned long currentMillis)
{
    if(currentMillis - serialPreviousMillis >= serialInterval) 
    {
        serialPreviousMillis = currentMillis;
        
        degreesCelsius = bmp.readTemperature();
        Serial.print("-Temperature = ");
        Serial.print(degreesCelsius);
        Serial.println(" *C");

        pressureReading = bmp.readPressure();
        Serial.print("Pressure = ");
        Serial.print(pressureReading);
        Serial.println(" Pa");
        Serial.println();    
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
    
    setupLedMatrix();
}


void setupLedMatrix()
{
    matrix.begin(0x70);  // pass in the address    
    
    matrix.setTextSize(1);
    matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
    matrix.setTextColor(LED_ON);
    matrix.setRotation(1);    
}
