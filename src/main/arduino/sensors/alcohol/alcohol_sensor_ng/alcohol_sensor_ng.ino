
/**
 * 
 * This project is intended for Adafruit 5V Trinket (Select USBtinyISP from the Tools->Programmer)
 * 
 * Alcohol sensor:
 * 
 *      https://www.seeedstudio.com/Grove-Alcohol-Sensor-p-764.html
 *    
 * 4-Digit 7-Segment LED Display Backpack
 * 
 *      https://www.adafruit.com/product/879
 * 
 * 4-Digit 7-Segment LED Display (yellow)
 * 
 *      https://www.adafruit.com/products/811
 * 
 * Adafrut 5V Trinket
 * 
 *     From Adafruit on Analog pins: 
 * 
 *          "Note the numbering of analog pins: Pin 2 is Analog 1, Pin 3 is Analog 3, Pin 4 is Analog 2. For the Uno, the terms A1, A2, and A3 are mapped for you. For ATtiny85's, they are not. So for the pinMode calls, use the Pin number (stenciled on Trinket), for analogRead, use the analog number."
 * 
 * Lipo Charger & 5V Booster
 * 
 *      https://www.adafruit.com/product/1944
 * 
 *      charger connector for an Arduino Uno
 * 
 *          https://www.adafruit.com/product/2697
 * 
 *          
 * 
 * For more project information, including wiring information, see the project Web
 * site.
 * 
 *   oneweb.elctoncis/sensors
 * 
 * Parts of this sketch were inspired by the Seeed Studio example code:
 * 
 *    
 *    https://github.com/Seeed-Studio/Grove_Alcohol_Sensor
 *    http://wiki.seeedstudio.com/wiki/Grove_-_Alcohol_Sensor
 * 
 */

#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
//#include <TinyWireM.h> // Enable this line if using Adafruit Trinket, Gemma, etc.

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();

/*
 * These next definitions of the ALCOHOL_DAT and HEATER_SEL
 * pins are for the Adafruit Trinket
 */
#define ALCOHOL_DAT_ANALOG_READ 2
#define ALCOHOL_DAT_PIN 4   
//#define HEATER_SEL  A3
#define HEATER_SEL_PIN 3

/** 
 * 
 * The next three commented declarations were the recommended original
 * threshold values from Seeed Studio.
 * 
int nearNoneThresholdMax = 200; // "No alcohol vapor detected"
int highThresholdMin = 600;  // "High Concentration of Alcohol detected"
int highThresholdMax = 750;  // "Very high Concentration of Alcohol detected"
 * 
 */
int sensorValue;

void setup()
{
//  Serial.begin(9600);  // open the serial port at 9600 bps
  
  pinsInit();
  switchOnHeater();
//  Serial.println("Start to heat the sensor, please wait 5~10min befor exposure to alcohol");
  
  setupLcdDisplay();
}

void loop()
{
    sensorValue = analogRead(ALCOHOL_DAT_ANALOG_READ); //read the analog value
  
    int value = 1023 - sensorValue;
  
    //Disply the results in serial monitor.
//    Serial.print("alcohol sensor: ");
  
    //sensorValue goes down when alcohol is detected. Hence subtracting from 1023.
//    Serial.print(value);
//    Serial.println();
    
    // print with print/println
    matrix.println(value);
    matrix.writeDisplay();    
          
    delay(700);
}

void pinsInit()
{
  pinMode(HEATER_SEL_PIN,OUTPUT);// set the HEATER_SEL as digital output.
  switchOffHeater(); //when HEATER_SEL is set, heater is switched off.
  pinMode(ALCOHOL_DAT_PIN,INPUT);
}

void setupLcdDisplay()
{
  matrix.begin(0x70);    
}

/*switch on the heater of Alcohol sensor*/
void switchOnHeater()
{
  digitalWrite(HEATER_SEL_PIN, LOW);
}
/*switch off the heater of Alcohol sensor*/
void switchOffHeater()
{
  digitalWrite(HEATER_SEL_PIN, HIGH);
}
