
/**
 * source code origianlly from
 * 
 *    https://learn.adafruit.com/adafruit-oled-featherwing?view=all
 *    
 * uses the following products   
 * 
 *    https://www.adafruit.com/products/2900
 *    
 *    
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
 #error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup() {  
  Serial.begin(9600);

  Serial.println("OLED FeatherWing test");
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  Serial.println("OLED begun");
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();
  
  Serial.println("IO test");

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Roberto Marquez");
  display.println("Software Developer");
  display.println("CWT Sato Travel");
  display.println("rmarquez@cwtsatotravel.com");
  display.setCursor(0,0);
  display.display(); // actually display all of the above
}


void loop() 
{
  display.setTextSize(1);
  if (! digitalRead(BUTTON_A)) 
  {
    
    display.clearDisplay();
    
    display.setCursor(0,0);
    display.println("Roberto Marquez");
    display.println("Maker");
    display.println("github.com/onebeartoe");
  }
  
  if (! digitalRead(BUTTON_B)) 
  {
    display.clearDisplay();
    
    display.setCursor(0,0);
    display.println("Roberto Marquez");
    display.println("Dude");
    display.println("twitter.com/onebeartoe");
    display.println("210 370 7207");
  }
  
  if (! digitalRead(BUTTON_C))
  {
    display.clearDisplay();

    display.setTextSize(2);
    
    display.setCursor(4,2);
    display.print("I love you");
//    display.startscrollright(0x00, 0x0F);
  }
  
  delay(10);
  yield();
  display.display();
}
