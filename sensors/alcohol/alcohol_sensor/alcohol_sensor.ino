/**
 * 
 * This code originally came from
 * 
 *    https://github.com/Seeed-Studio/Grove_Alcohol_Sensor
 *    
 * Hookup via the Grove base shield and alcohol sensor
 * 
 *    connect the alcohol sensor to the A0 port on the Grove base shield.
 * 
 */


/*
 * DetectAlcoholVapor.ino
 * Example sketch for Grove Alcohol Sensor
 *
 * Copyright (c) 2012 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Frankie.Chu
 * Create Time: Jan 21,2013
 * Change Log :
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
/*macro definitions of Alcohol Sensor's pins*/
#define ALCOHOL_DAT A0
#define HEATER_SEL  A1

void setup()
{
  Serial.begin(9600);  // open the serial port at 9600 bps
  pinsInit();
  switchOnHeater();
  Serial.println("Start to heat the sensor, please wait 5~10min befor exposure to alcohol");
}
void loop()
{
  int sensorValue;
  sensorValue = analogRead(ALCOHOL_DAT); //read the analog value
  int value = 1023 - sensorValue;
  //Disply the results in serial monitor.
  Serial.print("sensor test value = ");
  //sensorValue goes down when alcohol is detected. Hence subtracting from 1023.
  Serial.println(value);
  /*The information below is recommended result of the judgment*/
  if(value < 200)
    Serial.println("No alcohol vapor detected");
  else if((value > 600) && (value < 750))
    Serial.println("High Concentration of Alcohol detected");
  else
    Serial.println("Very high Concentration of Alcohol detected");
  delay(1000);
}

void pinsInit()
{
  pinMode(HEATER_SEL,OUTPUT);// set the HEATER_SEL as digital output.
  switchOffHeater(); //when HEATER_SEL is set, heater is switched off.
  pinMode(ALCOHOL_DAT,INPUT);
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

