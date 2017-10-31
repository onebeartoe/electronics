
/******************************************************************************
    This sketch i sbased on:

  MicroOLED_Hello.ino
  SFE_MicroOLED Hello World Demo
  Jim Lindblom @ SparkFun Electronics
  Original Creation Date: October 26, 2014
  
  This sketch lights up a familiar pattern on the MicroOLED
  Breakout. It's a great way to prove you've connected everything
  correctly and that your display is in working order.
  
  Hardware Connections:
    We'll be using the SPI interface on the MicroOLED, though it
    also supports I2C (and a really messy parallel). If you want
    to swap in I2C, read through the comments to find out how.
    
    MicroOLED ------------- Arduino
      GND ------------------- GND
      VDD ------------------- 3.3V (VCC)
    D1/MOSI ----------------- D11 (don't change)
    D0/SCK ------------------ D13 (don't change)
      D2
      D/C ------------------- D8 (can be any digital pin)
      RST ------------------- D9 (can be any digital pin)
      CS  ------------------- D10 (can be any digital pin)
    
  Development environment specifics:
  	IDE: Arduino 1.0.5
  	Hardware Platform: MicroOLED Breakout
                           Arduino Pro 3.3V/8MHz
  
  Note: The display on the MicroOLED is a 1.8V-3.3V device only.
  Don't try to connect a 5V Arduino directly to it! Use level
  shifters in between the data signals if you have to resort to
  a 5V board.
  
  Distributed as-is; no warranty is given.
*******************************************************************************/
#include <Wire.h>  // Include Wire if you're using I2C
//#include <SPI.h>  // Include SPI if you're using SPI
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library

//////////////////////////
// MicroOLED Definition //
//////////////////////////
#define PIN_RESET 9  // Connect RST to pin 9 (req. for SPI and I2C)
#define PIN_DC    8  // Connect DC to pin 8 (required for SPI)
#define PIN_CS    10 // Connect CS to pin 10 (required for SPI)
#define DC_JUMPER 1
// Also connect pin 13 to SCK and pin 11 to MOSI

//////////////////////////////////
// MicroOLED Object Declaration //
//////////////////////////////////
// Declare a MicroOLED object. The parameters include:
// 1 - Reset pin: Any digital pin
// 2 - D/C pin: Any digital pin (SPI mode only)
// 3 - CS pin: Any digital pin (SPI mode only, 10 recommended)
//MicroOLED oled(PIN_RESET, PIN_DC, PIN_CS);
MicroOLED oled(PIN_RESET, DC_JUMPER); // Example I2C declaration

// motor pins follow
#define MOTOR_A_INPUT_1 6
#define MOTOR_A_INPUT_2 7

int PWMA = A0;
int motorA = 5;

// I2C is great, but will result in a much slower update rate. The
// slower framerate may be a worthwhile tradeoff, if you need more
// pins, though.
void setup()
{
    Serial.begin(9600);

  // These three lines of code are all you need to initialize the
  // OLED and print the splash screen.
  
  // Before you can start using the OLED, call begin() to init
  // all of the pins and configure the OLED.
  oled.begin();
  // clear(ALL) will clear out the OLED's graphic memory.
  // clear(PAGE) will clear the Arduino's display buffer.
  oled.clear(ALL);  // Clear the display's memory (gets rid of artifacts)
  // To actually draw anything on the display, you must call the
  // display() function. 
  oled.display();

    pinMode(MOTOR_A_INPUT_1, OUTPUT);
    pinMode(MOTOR_A_INPUT_2, OUTPUT);

  pinMode(PWMA, OUTPUT);   // sets the pin as output

}



void loop()
{
    Serial.println("looper");

//    printTitle("Text!", 1);

    digitalWrite(MOTOR_A_INPUT_1, HIGH);
    digitalWrite(MOTOR_A_INPUT_2, LOW);

    motorA = 5;
    analogWrite(PWMA, motorA);

    delay(1000);
    
    motorA = 250;
 //   analogWrite(PWMA, motorA);

//    printTitle("Other", 1);
    digitalWrite(MOTOR_A_INPUT_1, LOW);
    digitalWrite(MOTOR_A_INPUT_2, HIGH);

}

// Center and print a small title
// This function is quick and dirty. Only works for titles one
// line long.
void printTitle(String title, int font)
{
  int middleX = oled.getLCDWidth() / 2;
  int middleY = oled.getLCDHeight() / 2;
  
  oled.clear(PAGE);
  oled.setFontType(font);
  // Try to set the cursor in the middle of the screen
  oled.setCursor(middleX - (oled.getFontWidth() * (title.length()/2)),
                 middleY - (oled.getFontWidth() / 2));
  // Print the title:
  oled.print(title);
  oled.display();
  delay(1500);
  oled.clear(PAGE);
}
