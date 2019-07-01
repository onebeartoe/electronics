
/**
 * This project is a tribute to G1 Decepticon Soundwave 
 */

/**
 * This project is intened for use wit the Arduino Uno
 */

/*************************************************** 
  This is a test example for the Adafruit Trellis w/HT16K33

  Designed specifically to work with the Adafruit Trellis 
  ----> https://www.adafruit.com/products/1616
  ----> https://www.adafruit.com/products/1611

  These displays use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include "Adafruit_Trellis.h"

#include <Adafruit_NeoPixel.h>

/**
 * This project also uses the Adafruit Wave Shield for Arduino
 * 
 *    https://www.adafruit.com/product/94
 * 
 */
#include "WaveUtil.h"
#include "WaveHC.h"

#include "NeoPatterns.h"

SdReader card;    // This object holds the information for the card
FatVolume vol;    // This holds the information for the partition on the card

FatReader root;   // This holds the information for the filesystem on the card

FatReader f;      // This holds the information for the file we're play

WaveHC wave;      // This is the only wave (audio) object, since we will only play one at a time


/*************************************************** 
  This example shows reading buttons and setting/clearing buttons in a loop
  "momentary" mode has the LED light up only when a button is pressed
  "latching" mode lets you turn the LED on/off when pressed

  Up to 8 matrices can be used but this example will show 4 or 1
 ****************************************************/

#define MOMENTARY 0
#define LATCHING 1
// set the mode here
#define MODE LATCHING 


Adafruit_Trellis matrix0 = Adafruit_Trellis();

// uncomment the below to add 3 more matrices
/*
Adafruit_Trellis matrix1 = Adafruit_Trellis();
Adafruit_Trellis matrix2 = Adafruit_Trellis();
Adafruit_Trellis matrix3 = Adafruit_Trellis();
// you can add another 4, up to 8
*/

// Just one
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);
// or use the below to select 4, up to 8 can be passed in
//Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0, &matrix1, &matrix2, &matrix3);

// set to however many you're working with here, up to 8
#define NUMTRELLIS 1

#define numKeys (NUMTRELLIS * 16)

// Connect Trellis Vin to 5V and Ground to ground.
// Connect the INT wire to pin #A2 (can change later!)
#define INTPIN A2
// Connect I2C SDA pin to your Arduino SDA line
// Connect I2C SCL pin to your Arduino SCL line
// All Trellises share the SDA, SCL and INT pin! 
// Even 8 tiles use only 3 wires max

#define PIXEL_PIN    6  // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 16  // Number of NeoPixels





NeoPatterns Ring2(PIXEL_COUNT, 6, NEO_GRB + NEO_KHZ800, 0);
    
    

void sdErrorCheck(void)
{
  if (!card.errorCode()) return;
  putstring("\n\rSD I/O error: ");
  Serial.print(card.errorCode(), HEX);
  putstring(", ");
  Serial.println(card.errorData(), HEX);
  while(1);
}

void setup() 
{
  Serial.begin(9600);
  Serial.println("Trellis Demo");

  // INT pin requires a pullup
  pinMode(INTPIN, INPUT);
  digitalWrite(INTPIN, HIGH);
  
  // begin() with the addresses of each panel in order
  // I find it easiest if the addresses are in order
  trellis.begin(0x70);  // only one
  // trellis.begin(0x70, 0x71, 0x72, 0x73);  // or four!

  // light up all the LEDs in order
  for (uint8_t i=0; i<numKeys; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();    
    delay(50);
  }
  // then turn them off
  for (uint8_t i=0; i<numKeys; i++) 
  {
    trellis.clrLED(i);
    trellis.writeDisplay();    
    delay(50);
  }
  
  
  //  if (!card.init(true)) { //play with 4 MHz spi if 8MHz isn't working for you
  if (!card.init()) {         //play with 8 MHz spi (default faster!)  
    putstring_nl("Card init. failed!");  // Something went wrong, lets print out why
    sdErrorCheck();
    while(1);                            // then 'halt' - do nothing!
  }
  
  // enable optimize read - some cards may timeout. Disable if you're having problems
  card.partialBlockRead(true);
 
// Now we will look for a FAT partition!
  uint8_t part;
  for (part = 0; part < 5; part++) {     // we have up to 5 slots to look in
    if (vol.init(card, part)) 
      break;                             // we found one, lets bail
  }
  if (part == 5) {                       // if we ended up not finding one  :(
    putstring_nl("No valid FAT partition!");
    sdErrorCheck();      // Something went wrong, lets print out why
    while(1);                            // then 'halt' - do nothing!
  }
  
  // Lets tell the user about what we found
  putstring("Using partition ");
  Serial.print(part, DEC);
  putstring(", type is FAT");
  Serial.println(vol.fatType(),DEC);     // FAT16 or FAT32?
  
  // Try to open the root directory
  if (!root.openRoot(vol)) {
    putstring_nl("Can't open root dir!"); // Something went wrong,
    while(1);                             // then 'halt' - do nothing!
  }
  
    // Whew! We got past the tough parts.
    putstring_nl("Ready!");  
  
  
    // Neopixel setup
    Ring2.begin();
    Ring2.Color1 = Ring2.Color(128, 0, 128);
    Ring2.Color2 = Ring2.Color(0,0,0);
    
    int interval = 200;
        
    int steps = Ring2.numPixels();
    
    Ring2.Fade(Ring2.Color1, Ring2.Color2, steps, interval);
}


void loop() 
{
    delay(30); // 30ms delay is required, dont remove me!
  
  if (MODE == MOMENTARY) {
    // If a button was just pressed or released...
    if (trellis.readSwitches()) {
      // go through every button
      for (uint8_t i=0; i<numKeys; i++) {
	// if it was pressed, turn it on
	if (trellis.justPressed(i)) {
	  Serial.print("v"); Serial.println(i);
          
          handleButtonPress(i);
          
	  trellis.setLED(i);
	} 
	// if it was released, turn it off
	if (trellis.justReleased(i)) {
	  Serial.print("^"); Serial.println(i);
	  trellis.clrLED(i);
	}
      }
      // tell the trellis to set the LEDs we requested
      trellis.writeDisplay();
    }
  }

    if (MODE == LATCHING) 
    {
        // If a button was just pressed or released...
        if (trellis.readSwitches()) 
        {
            // go through every button
            for (uint8_t i=0; i<numKeys; i++) 
            {
                // if it was pressed...
                if (trellis.justPressed(i)) 
                {
                    Serial.print("v"); Serial.println(i);
    
                    handleButtonPress(i);
          
                    // Alternate the LED
                    if (trellis.isLED(i))
                        trellis.clrLED(i);
                    else
                        trellis.setLED(i);
                } 
            }
            
            // tell the trellis to set the LEDs we requested
            trellis.writeDisplay();
        }
    }
  
    // update the neopixels
    //    theaterChaseRainbow();  
    Ring2.Update();
    
}

void handleButtonPress(uint8_t index)
{
    String wavfile = String(index) + ".wav";          
    playcomplete( wavfile.c_str() );    
}

// Plays a full file from beginning to end with no pause.
void playcomplete(char *name) {
  // call our helper to find and play this name
  playfile(name);
  while (wave.isplaying) {
  // do nothing while its playing
  }
  // now its done playing
}

void playfile(char *name) {
  // see if the wave object is currently doing something
  if (wave.isplaying) {// already playing something, so stop it!
    wave.stop(); // stop it
  }
  // look in the root directory and open the file
  if (!f.open(root, name)) {
    putstring("Couldn't open file "); Serial.print(name); return;
  }
  // OK read the file and turn it into a wave object
  if (!wave.create(f)) {
    putstring_nl("Not a valid WAV"); return;
  }
  
  // ok time to play! start playback
  wave.play();
}
