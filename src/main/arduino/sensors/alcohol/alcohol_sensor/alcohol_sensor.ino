
/**
 * 
 * For project information, including wiring information, see the project Web
 * site.
 * 
 *   oneweb.elctoncis/sensors
 * 
 * Parts of this sketch were inspired by the Seeed Studio example code:
 * 
 *    https://www.seeedstudio.com/Grove-Alcohol-Sensor-p-764.html
 *    https://github.com/Seeed-Studio/Grove_Alcohol_Sensor
 *    http://wiki.seeedstudio.com/wiki/Grove_-_Alcohol_Sensor
 * 
 */

#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
//#include <TinyWireM.h> // Enable this line if using Adafruit Trinket, Gemma, etc.

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();

/**
 * macro definitions of Alcohol Sensor's pins
 */
#define ALCOHOL_DAT A0
#define HEATER_SEL  A1

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
  Serial.begin(9600);  // open the serial port at 9600 bps
  
  pinsInit();
  switchOnHeater();
  Serial.println("Start to heat the sensor, please wait 5~10min befor exposure to alcohol");
  
  setupLcdDisplay();
}

void loop()
{
    sensorValue = analogRead(ALCOHOL_DAT); //read the analog value
  
    int value = 1023 - sensorValue;
  
    //Disply the results in serial monitor.
    Serial.print("alcohol sensor: ");
  
    //sensorValue goes down when alcohol is detected. Hence subtracting from 1023.
    Serial.print(value);
    Serial.println();
    
    // print with print/println
    matrix.println(value);
    matrix.writeDisplay();    
          
    delay(700);
}

void pinsInit()
{
  pinMode(HEATER_SEL,OUTPUT);// set the HEATER_SEL as digital output.
  switchOffHeater(); //when HEATER_SEL is set, heater is switched off.
  pinMode(ALCOHOL_DAT,INPUT);
}

void setupLcdDisplay()
{
  matrix.begin(0x70);    
}

/*switch on the heater of Alcohol sensor*/
void switchOnHeater()
{
  digitalWrite(HEATER_SEL,LOW);
}
/*switch off the heater of Alcohol sensor*/
void switchOffHeater()
{
  digitalWrite(HEATER_SEL,HIGH);
}

