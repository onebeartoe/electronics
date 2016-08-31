
/**
 * The project uses an
 * 
 * Arduino Uno
 * 
 * Grove Base Shield
 * 
 * Grove RGB Backlit LCD Display
 * 
 * Hookup the HC-SR04 distance sensor as follows:
 * 
 * Arduino digital pin -> HC-SR04 lead
 * 
 *      attach pin 2 to vcc
 *      attach pin 5 to GND
 *      attach pin 3 to Trig
 *      attach pin 4 to Echo
 * 
 */

#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const char BLANK_LINE[] = "                ";

void checkDistance(long distance)
{
    if(distance < 0.6)
    {
        // the distance is really really close, show red
        lcd.setRGB(255, 0, 0);
    }
    else if(0.6 <= distance && distance < 1.9)
    {
        // the distance is in the 'heads up' range, show blue
        lcd.setRGB(0, 0, 255);
    }
    else if(1.9 <= distance)
    {
        // the distance is in the 'okay' range, show green
        lcd.setRGB(0, 255, 0);
    }
    else
    {
        // show pink for unrecognized values
        lcd.setRGB(255, 105, 180);
    }
}

void setup() 
{
    // initialize serial communication:
    Serial.begin(9600);
    
    // setup the distance sensor
    pinMode (2,OUTPUT);//attach pin 2 to vcc
    pinMode (5,OUTPUT);//attach pin 5 to GND
  
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    // Print a message to the LCD.
    lcd.print("    Meters:");
    
    lcd.display();
}

void loop()
{
    float distance = readDistanceSensor();
  
    serialOutput(distance);
    
    checkDistance(distance);
    
    updateLcdDisplay(distance);

    delay(800);
}

/**
 * This function take the distance sensor value and converts it to centimeters
 * @param microseconds
 * @return 
 */
long microsecondsToCentimeters(long microseconds)
{
    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
    // The ping travels out and back, so to find the distance of the
    // object we take half of the distance travelled.
    return microseconds / 29 / 2;
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second). This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

float readDistanceSensor()
{
    digitalWrite(2, HIGH);
    // establish variables for duration of the ping,
    // and the distance result in inches and centimeters:
    long duration;
    long cm;
  
    // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    pinMode(3, OUTPUT);// attach pin 3 to Trig
    digitalWrite(3, LOW);
    delayMicroseconds(2);
    digitalWrite(3, HIGH);
    delayMicroseconds(5);
    digitalWrite(3, LOW);
    // The same pin is used to read the signal from the PING))): a HIGH
    // pulse whose duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode (4, INPUT);//attach pin 4 to Echo
    duration = pulseIn(4, HIGH);
  
    // convert the time into a distance
    cm = microsecondsToCentimeters(duration);
    
    float distance = cm / 100.0f;

    return distance;
}

void serialOutput(float distance)
{
    Serial.print(distance);
    Serial.print("cm");
    Serial.println();
}

/**
 * This function clears out the second row of the LCD display and
 * prints the distance there.
 * 
 * @param distance
 */
void updateLcdDisplay(float distance)
{
    // move the cursor to the second row and blank out all characters
    lcd.setCursor(0, 1);
    lcd.print(BLANK_LINE);
  
    // show the value on the LCD display
    lcd.setCursor(0, 1);
    lcd.print(distance);
}