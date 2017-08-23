
// uses Adafruit GEMMA

/**
 * This was originally used for the onebeartoe Arkenstone Neo Jewel pendant.
 * 
 * 
// Low power NeoPixel earrings example.  Makes a nice blinky display
// with just a few LEDs on at any time...uses MUCH less juice than
// rainbow display!

* Uses the following products from adafruit.com

     Gemma
     https://www.adafruit.com/products/1222

     NeoPixel Ring (16 count)
     https://www.adafruit.com/product/1463

     LiPo Battery
     https://www.adafruit.com/product/1317
     
*/
#include <Adafruit_NeoPixel.h>

#define PIN 1

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(32, PIN);

uint8_t  offset = 0; // Position of spinny eyes

uint32_t pink  = 0xFF00FF;
//uint32_t green  = 0x00FF00;
uint32_t purple  = 0x7D26CD;
uint32_t color  = pink; // start out with pink as the color

uint32_t prevTime;

int ledPin = 1;

// Generally, you shuould use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 1000;           // interval at which to blink (milliseconds)

void loop() 
{
  medal();
}

void medal()
{
  uint8_t  i;
  uint32_t t;



    i = random(32);
    pixels.setPixelColor(i, color);
    pixels.show();
    delay(10);
    pixels.setPixelColor(i, 0);
    
  
  t = millis();
  if((t - prevTime) > 8000) 
  {      
    // Every 8 seconds...

    // flip flop the current color
    if(color == pink)
    {
      color = purple;
    }
    else
    {
      color = purple;
    }

    for(i=0; i<32; i++) 
    {
      pixels.setPixelColor(i, 0);
    }
    
    prevTime = t;
  }  
}

void setup() 
{
  // medal
  pixels.begin();
  pixels.setBrightness(60); // 1/3 brightness
  prevTime = millis();
}

