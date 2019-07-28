

#ifndef onebeartoe_OledFeatherWing_h
#define onebeartoe_OledFeatherWing_h

#include <Adafruit_SSD1306.h>

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/ArduinoLoopTask.h"

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

byte stubornButtons[] = {BUTTON_A, BUTTON_B, BUTTON_C}; 

// This handy macro lets us determine how big the array up above is, by checking the size
#define NUMBUTTONS 3
//#define NUMBUTTONS sizeof(buttons)

#define DEBOUNCE     10 // button debouncer, how many ms to debounce, 5+ ms is usually plenty

class OledFeatherWing : public ArduinoLoopTask
{
    public:

        // here is where we define the buttons that we'll use. button "1" is the first, button "6" is the 6th, etc
        byte buttons[3] = {stubornButtons[0],stubornButtons[1],stubornButtons[2]}; 
        
        // we will track if a button is just pressed, just released, or 'currently pressed' 
        byte pressed[NUMBUTTONS], justpressed[NUMBUTTONS], justreleased[NUMBUTTONS];

        // TODO: DELETE THESE ONCE NETWORKING IS IMPLEMENTED
        int p1Score = 0;
        
        int p2Score = 0;

        int HUE;

        int state = P1_STATE;
        
        const int P1_STATE = 1;

        const int P2_STATE = 2;
        
        OledFeatherWing(Adafruit_SSD1306* display);
    
        virtual void aButtonPressed();
        
        virtual void oneLoop();
    
        virtual void check_switches();
        
//    private:
};

#endif
