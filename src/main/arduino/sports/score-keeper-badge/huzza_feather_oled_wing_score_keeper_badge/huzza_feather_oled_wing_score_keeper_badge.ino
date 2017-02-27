
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
 *    Feather 32u4 Bluefruit LE
 * 
 *          https://www.adafruit.com/products/2829
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 oled = Adafruit_SSD1306();

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
// we will track if a button is just pressed, just released, or 'currently pressed' 
byte pressed[NUMBUTTONS], justpressed[NUMBUTTONS], justreleased[NUMBUTTONS];

const int P1_STATE = 1;
const int P2_STATE = 2;

int state = P1_STATE;

// TODO: DELETE THESE ONCE NETWORKING IS IMPLEMENTED
int p1Score = 0;
int p2Score = 0;

char  displayText [4][50];

#define DEBOUNCE     10 // button debouncer, how many ms to debounce, 5+ ms is usually plenty

//int HUE;

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

    oled.display();
}

/**
 * This function is called when ever the 'mode' button is pressed.
 */
void bButtonPressed()
{
    char * stateLabel;
    if(state == P1_STATE)
    {
        state = P2_STATE;
        stateLabel = "Player1";
    }
    else if(state == P2_STATE)
    {
        state = P1_STATE;
        stateLabel = "Player2";
    }
    
    Serial.printf("state changed to %s", stateLabel);
}

void cButtonPressed()
{
    if(state == P1_STATE)
    {
        p1Score--;
    }
    else if(state == P2_STATE)
    {
        p2Score--;
    }
    
    // TODO: Implement the rest
}

void check_switches()
{
    static byte previousstate[NUMBUTTONS];
    static byte currentstate[NUMBUTTONS];
    static long lasttime;
    byte index;

    if (millis() < lasttime)
    { 
        // we wrapped around, lets just try again
       lasttime = millis();
    }
  
    if ((lasttime + DEBOUNCE) > millis()) 
    {
      // not enough time has passed to debounce
      return; 
    }
    
    // ok we have waited DEBOUNCE milliseconds, lets reset the timer
    lasttime = millis();
  
    for (index = 0; index<NUMBUTTONS; index++)
    { 
        // when we start, we clear out the "just" indicators
        justreleased[index] = 0;

        currentstate[index] = digitalRead(buttons[index]);   // read the button

        if (currentstate[index] == previousstate[index]) 
        {
          if ((pressed[index] == LOW) && (currentstate[index] == LOW)) 
          {
              // just pressed
              justpressed[index] = 1;
          }
          else if ((pressed[index] == HIGH) && (currentstate[index] == HIGH)) 
          {
              // just released
              justreleased[index] = 1;
          }
          pressed[index] = !currentstate[index];  // remember, digital HIGH means NOT pressed
        }
        //Serial.println(pressed[index], DEC);
        previousstate[index] = currentstate[index];   // keep a running tally of the buttons
    }
}

void displayScore()
{
    oled.clearDisplay();    
    oled.setCursor(0,0);
    oled.print("P1: ");
    oled.print(p1Score);
    oled.print(" - P2:");
    oled.print(p2Score);
    oled.display();
}

void loop() 
{
    // when we check the switches we'll get the current state
    check_switches();      

    for (byte i = 0; i<NUMBUTTONS; i++)
    {
        if (pressed[i]) 
        {
            // is the button pressed down at this moment
            Serial.printf("button %d is pressed.\n", i);            
        }
        
        // this is the code block to use for detecting button presses (when the 
        // button is actually releaed).
        if (justreleased[i])
        {
            if (i == 0)
            {  
              Serial.printf("button %d is released.\n", i);
              
              aButtonPressed();
            }
            else if (i == 1)
            {
                Serial.printf("button B is released.\n", i);
                
                bButtonPressed();
            }
            else if (i == 2)
            {
                Serial.printf("button %d is released.\n", i);
                
                cButtonPressed();
            }

            for (byte i=0; i<NUMBUTTONS; i++)
            {  
                // remember, check_switches() will necessitate clearing the 'just pressed' flag
                justpressed[i] = 0;
            }
        }
    }
    
    delay(10);
    yield();
    oled.display();
}

void setup() 
{
    Serial.begin(9600);

    Serial.println("OLED FeatherWing test");
    // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
    // init done
    Serial.println("OLED begun");
  
    // Show image buffer on the OLED display hardware.
    // Since the buffer is intialized with an Adafruit splashscreen
    // internally, this will display the splashscreen.
    oled.display();
    delay(1000);

    // Clear the buffer.
    oled.clearDisplay();
    oled.display();

    Serial.println("Score Keeper Badge");

    // set the button pins as inputs and enable their pull-up resistors
    for (int i=0; i<NUMBUTTONS; i++)
    {
      pinMode(buttons[i], INPUT_PULLUP);
    }

    oled.setTextSize(1);
    oled.setTextColor(WHITE);
    oled.setCursor(0,0);
    oled.println("     Score Keeper");
    oled.println("          by");
    oled.println("electronics.onebeartoe.org");
    oled.setCursor(0,0);
    
    oled.display(); // actually display all of the above on the OLED
}