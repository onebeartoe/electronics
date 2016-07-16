#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();

static const uint8_t PROGMEM
  smile_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100 },
  neutral_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10111101,
    B10000001,
    B01000010,
    B00111100 },
  frown_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10011001,
    B10100101,
    B01000010,
    B00111100 };


void setup() {

//  Serial.begin(9600);
//  Serial.println("ISSI manual animation test");
  if (! matrix.begin()) {
  //  Serial.println("IS31 not found");
    while (1);
  }
//  Serial.println("IS31 Found!");
  
}

void loop() 
{
  matrix.setRotation(0);

  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(100);
  for (int8_t x=0;
            x>=-200;
//            x>=-100;  // too short
//            x>=-300;  // too long
//            x>=-400;
//          x>=-500;
//          x>=-550;
//        x>=-600;
//        x>=-632; 
        x--) 
  {
    matrix.clear();
    matrix.setCursor(x,1);
    matrix.print("Hello, my name is Roberto!");
    delay(100);
  }
}
