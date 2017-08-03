
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

#define PIN_BUTTON_CAPITAL_A 0
#define PIN_BUTTON_STRING    2

void setup()
{
  // button pins as inputs
  pinMode(PIN_BUTTON_CAPITAL_A, INPUT);
  pinMode(PIN_BUTTON_STRING, INPUT);

  // setting input pins to high means turning on internal pull-up resistors
  digitalWrite(PIN_BUTTON_CAPITAL_A, HIGH);
  digitalWrite(PIN_BUTTON_STRING, HIGH);
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

	pollButtons();
}

void pollButtons()
{
	if (digitalRead(PIN_BUTTON_CAPITAL_A) == LOW)
    {
      // this should type a capital A
  //    TrinketKeyboard.pressKey(KEYCODE_MOD_LEFT_SHIFT, KEYCODE_A);

      // Press alt + shift + o (Open Resource in Netbeans)
//      TrinketKeyboard.pressKey(KEYCODE_RIGHT_ALT, KEYCODE_RIGHT_SHIFT, KEYCODE_O);

      // Press Ctrl + a (select all)
      TrinketKeyboard.pressKey(KEYCODE_MOD_LEFT_CONTROL, KEYCODE_A);

      // this releases the key (otherwise it is held down!)
      TrinketKeyboard.pressKey(0, 0);

      delay(1000);
    }

    if (digitalRead(PIN_BUTTON_STRING) == LOW)
    {
      // type out a string using the Print class
      TrinketKeyboard.print("Hello World!");
    }
}
