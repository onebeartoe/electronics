
/**
 * The project uses the following parts
 * 
 * Mini Pan-Tilt Kit - Assembled with Micro Servos
 * 
 *      https://www.adafruit.com/products/1967
 * 
 * Arduino Uno
 * 
 * Grove Base Shield
 * 
 * Grove RGB Backlit LCD Display
 * 
 * Grove Sliding Potentiometer v1.0
 * 
 */

#include <Servo.h>
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

#define SERVO_PIN 9

/**
 * The SERVO_DELAY of 300 give a real jerky almost like a baby chicken.
 * 
 * A value of 15 is from the Arduino examples
 * 
 *      http://playground.arduino.cc/ComponentLib/Servo
 */
#define SERVO_DELAY 150

long analog0 = -1;

const char BLANK_LINE[] = "                ";

Servo vineServo;

/**
 * This function has to attach and detach the servo each time to avoid the jitter issue seen while also using SerialSoftware.h
*/
void moveServo(int angle)
{
  vineServo.attach(SERVO_PIN);  

  vineServo.write(angle); 
  delay(SERVO_DELAY);

  vineServo.detach();  
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
    lcd.print("Analog 0:");
    
    lcd.display();
}

void loop()
{
    int read0 = analogRead(A0);
//    Serial.println(read0);
    
    if(analog0 != read0)
    {
        analog0 = read0;
        
        int angle = map(analog0, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180)
        moveServo(angle);
        
        serialOutput(analog0);
        updateLcdDisplay(analog0);
    }

    delay(80);
}

void serialOutput(long analog0)
{
    Serial.print("analog 0: ");
    Serial.print(analog0);    
    Serial.println();
}

/**
 * This function clears out the second row of the LCD display and
 * prints the distance there.
 * 
 * @param distance
 */
void updateLcdDisplay(long analog0)
{
    // move the cursor to the second row and blank out all characters
    lcd.setCursor(0, 1);
    lcd.print(BLANK_LINE);
  
    // show the value on the LCD display
    lcd.setCursor(0, 1);
    lcd.print(analog0);
}
