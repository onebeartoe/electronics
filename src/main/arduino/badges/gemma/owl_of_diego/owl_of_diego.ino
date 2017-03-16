
/**
  * This is pretty much the hair stick example, using the colors that Diego suggested.
  */
          
//https://learn.adafruit.com/jewel-hair-stick

/**
// Low power NeoPixel earrings example.  Makes a nice blinky display
// with just a few LEDs on at any time...uses MUCH less juice than
// rainbow display!

* Uses the following products from adafruit.com

    Gemma
    https://www.adafruit.com/products/1222

 *  NeoPixel Jewel - 7 x 5050 RGB LED with Integrated Drivers
 *  https://www.adafruit.com/products/2226
 * 
 * 
*/


/* 
Jewel Hairstick by Leslie Birch for Adafruit Industries
Based on NeoPixel Library by Adafruit
*/
 
// This section is NeoPixel Variables
 
#include <Adafruit_NeoPixel.h>
 
#define PIN 1
 
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(7, 1, NEO_GRB + NEO_KHZ800);

// Diego picked these colors.  Use the regular RBG and then the three colors 
//  that come from those next to the dot.  
uint32_t color1 = strip.Color(130, 0, 0); // red
uint32_t color2 = strip.Color(130, 130, 0); // yellow
uint32_t color3 = strip.Color(0, 130, 0); //green
uint32_t color4 = strip.Color(0, 130, 130); // teal
uint32_t color5 = strip.Color(0, 0, 130); // blue

//long colorChangeDelay = 3000;
long colorChangeDelay = 1000;

void setup() 
{
   //This is for Neopixel Setup
  strip.begin();

  strip.setBrightness(30);
  
  strip.show(); // Initialize all pixels to 'off'
}
 
void loop() 
{
  // the first number is the pixel number for Jewel. O is the center one 
  strip.setPixelColor(1, color1); 
  strip.setPixelColor(2, color1); 
  strip.setPixelColor(3, color1); 
  strip.setPixelColor(4, color1); 
  strip.setPixelColor(5, color1); 
  strip.setPixelColor(6, color1); 
  strip.setPixelColor(0, color2); 
  
  strip.show();
  delay(colorChangeDelay);
  
  
  strip.setPixelColor(1, color2); 
  strip.setPixelColor(2, color2); 
  strip.setPixelColor(3, color2); 
  strip.setPixelColor(4, color2); 
  strip.setPixelColor(5, color2); 
  strip.setPixelColor(6, color2); 
  strip.setPixelColor(0, color3); 
  
  strip.show();
  delay(colorChangeDelay);
  
  strip.setPixelColor(1, color3); 
  strip.setPixelColor(2, color3); 
  strip.setPixelColor(3, color3);
  strip.setPixelColor(4, color3); 
  strip.setPixelColor(5, color3); 
  strip.setPixelColor(6, color3); 
  strip.setPixelColor(0, color4); 
  
  strip.show();
  delay(colorChangeDelay);
  
  strip.setPixelColor(1, color4); 
  strip.setPixelColor(2, color4); 
  strip.setPixelColor(3, color4); 
  strip.setPixelColor(4, color4); 
  strip.setPixelColor(5, color4); 
  strip.setPixelColor(6, color4); 
  strip.setPixelColor(0, color5); 
  
  strip.show();
  delay(colorChangeDelay);
  
  strip.setPixelColor(1, color5); 
  strip.setPixelColor(2, color5); 
  strip.setPixelColor(3, color5);
  strip.setPixelColor(4, color5); 
  strip.setPixelColor(5, color5); 
  strip.setPixelColor(6, color5); 
  strip.setPixelColor(0, color1); 
  
  strip.show();
  delay(colorChangeDelay); 
}