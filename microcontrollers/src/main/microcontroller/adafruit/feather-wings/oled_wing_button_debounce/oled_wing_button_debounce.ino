/**
 * 
 * This code demonstrates how to debounce the 3 buttons on the Adafruit OLED 
 * Feather Wing.  See the 'if (justreleased[i])' conditional in the loop() function
 * to see how/where to execute code when one of the buttons is released after being pressed.
 * 
 * source code originally from
 * 
 *    https://learn.adafruit.com/adafruit-oled-featherwing?view=all
 *    
 * This project works with esp8266 Community version 2.2.0 (or better) library for Arduino 1.6.13
 * 
 * uses the following products   
 * 
 *    FeatherWing OLED - 128x32        
 *
 *          https://www.adafruit.com/products/2900
 *    
 *    
 *    Feather 32u4 Bluefruit LE
 * 
 *          https://www.adafruit.com/products/2829
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306();

#if defined(ESP8266)
  #define BUTTON_A 0
  #define BUTTON_B 16
  #define BUTTON_C 2
  #define LED      0
#elif defined(ARDUINO_STM32F2_FEATHER)
  #define BUTTON_A PA15
  #define BUTTON_B PC7
  #define BUTTON_C PC5
  #define LED PB5
#elif defined(TEENSYDUINO)
  #define BUTTON_A 4
  #define BUTTON_B 3
  #define BUTTON_C 8
  #define LED 13
#else 
  #define BUTTON_A 9
  #define BUTTON_B 6
  #define BUTTON_C 5
  #define LED      13
#endif

#if (SSD1306_LCDHEIGHT != 32)
// TODO: Uncomment this next line for production.
//       It is only commented because Netbeans takes it for an unrecognized command
//       and syntax highlighting is broken after this line.
// #error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// here is where we define the buttons that we'll use. button "1" is the first, button "6" is the 6th, etc
byte buttons[] = {BUTTON_A, BUTTON_B, BUTTON_C}; 
// This handy macro lets us determine how big the array up above is, by checking the size
#define NUMBUTTONS sizeof(buttons)



const int P1_STATE = 1;
const int P2_STATE = 2;

int state = P1_STATE;

// TODO: DELETE THESE ONCE NETWORKING IS IMPLEMENTED
int p1Score = 0;
int p2Score = 0;

char  displayText [4][50];

#define DEBOUNCE     10 // button debouncer, how many ms to debounce, 5+ ms is usually plenty

int HUE;


#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/microcontroller/adafruit/feather-wings/oled/src/OledFeatherWing.h"
#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/microcontroller/adafruit/feather-wings/oled/src/OledFeatherWing.cpp"


OledFeatherWing oledWing = OledFeatherWing(&display);
//OledFeatherWing oledWing;
//OledFeatherWing* oledWing;

void aButtonPressed()
{
    if(state == P1_STATE)
    {
        p1Score++;        
    }
    else if(state == P2_STATE)
    {
        p2Score++;
    }
    else
    {
        Serial.println("ERROR: an unknown state was found: " + state);
    }
    
    display.clearDisplay();    
    display.setCursor(0,0);
    display.print("P1: ");
    display.print(p1Score);
    display.print(" - P2:");
    display.print(p2Score);    
}



void setup() 
{
  Serial.begin(9600);

  Serial.println("OLED FeatherWing test");
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  Serial.println("OLED begun...");
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();
  
  Serial.println("IO test");

  // Make input & enable pull-up resistors on switch pins
  for (int i=0; i<NUMBUTTONS; i++)
  {
    pinMode(buttons[i], INPUT_PULLUP);
  }  

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("     Score Keeper");
  display.println("          by");
  display.println("electronics.onebeartoe.org");
  display.setCursor(0,0);
  display.display(); // actually display all of the above
}

void loop() 
{    
    oledWing.loop();
}
