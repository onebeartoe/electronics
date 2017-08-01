
/**
 * I tried this but it didnto work on an installed library in the Arduino IDE.
 *
 *      https://learn.adafruit.com/trinket-usb-keyboard/overview
 *
 * To get the sketch to compile, this library was installed into the user Arduino folder
 *
 *      https://github.com/adafruit/Adafruit-Trinket-USB/tree/master/TrinketKeyboard
 *
 * TrinketKeyboard example
 * For Trinket by Adafruit Industries
*/

#include <TrinketKeyboard.h>

#include "relative-path-includes.h"

#define PIN_BUTTON_A 0
#define PIN_BUTTON_B 2

int buttonCount = 2;
int buttonPins[] = {PIN_BUTTON_A,
					PIN_BUTTON_B};

NetbeansIdeShortcuts ideShortcuts = NetbeansIdeShortcuts();
//IdeShortcuts ideShortcuts = NetbeansIdeShortcuts();

void setup()
{
  // button pins as inputs
  pinMode(PIN_BUTTON_A, INPUT);
  pinMode(PIN_BUTTON_B, INPUT);

  // setting input pins to high means turning on internal pull-up resistors
  digitalWrite(PIN_BUTTON_A, HIGH);
  digitalWrite(PIN_BUTTON_B, HIGH);
  // remember, the buttons are active-low, they read LOW when they are not pressed

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
			ideShortcuts.openType();

	      	// this releases the key (otherwise it is held down!)
	      	TrinketKeyboard.pressKey(0, 0);

	  		// debounce a little
	      	delay(1000);
		}
    }
}
