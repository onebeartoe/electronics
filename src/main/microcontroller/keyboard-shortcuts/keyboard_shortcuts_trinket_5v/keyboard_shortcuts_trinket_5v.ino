
#include "board-setup.h"
#include "troubleshooting.h"

#include <TrinketKeyboard.h>

#include "relative-path-includes.h"

#define PIN_BUTTON_A_OPEN_TYPE 0
#define PIN_BUTTON_A_OPEN_RESOURCE 2
#define BUTTON_PIN_ORGANIZE_IMPORTS 1
#define BUTTON_PIN_FIND_IN_FILES 4

const int buttonCount = 2;
int buttonPins[] = {PIN_BUTTON_A_OPEN_RESOURCE,
                    PIN_BUTTON_A_OPEN_TYPE,
                    BUTTON_PIN_ORGANIZE_IMPORTS,
                    BUTTON_PIN_FIND_IN_FILES};

NetbeansIdeShortcuts netbeansShortcuts = NetbeansIdeShortcuts();

/**
 * Using the pointer allows for the 'polymorhism' as described in this
 * stackoverflow answer:
 *
 *       https://stackoverflow.com/a/33123456/803890
 */
IdeShortcuts* ideShortcuts[1] = {&netbeansShortcuts};

int ideIndex = 0;

void setup()
{
    pinMode(PIN_BUTTON_A_OPEN_TYPE, INPUT);
    pinMode(PIN_BUTTON_A_OPEN_RESOURCE, INPUT);
    pinMode(BUTTON_PIN_ORGANIZE_IMPORTS, INPUT_PULLUP);
//    pinMode(BUTTON_PIN_FIND_IN_FILES, INPUT_PULLUP);

    // setting input pins to high means turning on internal pull-up resistors
    digitalWrite(PIN_BUTTON_A_OPEN_TYPE, HIGH);
    digitalWrite(PIN_BUTTON_A_OPEN_RESOURCE, HIGH);
//    digitalWrite(BUTTON_PIN_ORGANIZE_IMPORTS, HIGH);
//    digitalWrite(BUTTON_PIN_FIND_IN_FILES, HIGH);

/*
//	Doh! for some reason using the for loop to initialize and set the pull up resistors
//	on the pins was causing unexpected behavior 
	for(int i=0; i++; i<buttonCount)
	{
		// button pins as inputs
	    pinMode(buttonPins[i], INPUT);

	    // setting input pins to high means turning on internal pull-up resistors
	    digitalWrite(buttonPins[i], HIGH);

	    // remember, the buttons are active-low, they read LOW when they are not pressed
	}
*/

  // start USB stuff
  TrinketKeyboard.begin();
}

void loop()
{
	// the poll function must be called at least once every 10 ms
	// or cause a keystroke
	// if it is not, then the computer may think that the device
	// has stopped working, and give errors
	TrinketKeyboard.poll();

	pollButtonPins();
}

void pollButtonPins()
{
    for(int i=0; i<buttonCount; i++)
    {
        int pinState = digitalRead(buttonPins[i]);

        if(pinState == LOW)
        {
            pressKeysForPin(i);

            // this releases the key (otherwise it is held down!)
            TrinketKeyboard.pressKey(0, 0);

            // debounce a little
//            delay(50);
        }
    }
}

void pressKeysForPin(int shorcutIndex)
{
    switch(shorcutIndex)
    {
        case 0:
        {
            ideShortcuts[ideIndex]->openType();

            break;
        }
        case 1:
        {
            ideShortcuts[ideIndex]->openResource();

            break;
        }
        case 2:
        {
            ideShortcuts[ideIndex]->findInProjects();
            
            break;
        }
        case 3:
        {
            ideShortcuts[ideIndex]->organizeImports();
            
            break;
        }
        default :
        {
            // do nothing
        }
    }
}
