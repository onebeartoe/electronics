// Scrolling cloud pendant for Adafruit Pro Trinket and ST7735R display.
// Inspired by Cory Arcangel's "Super Mario Clouds."
// Triggered with vibration switch between digital pins 3 and 4.

// This is NOT a good learning example for the Adafruit_GFX library!
// To achieve fast frame rates, the code does horrible irresponsible
// things, bypassing the GFX lib and issuing commands & data directly
// to the LCD driver.  It's hardcoded for specific control pins, not
// portable to other displays, and other such crimes.
// Look at the ST7735R library examples for better role models.

// As part of the optimization strategy, everything's drawn sideways;
// clouds scroll "up," not across.  Mount TFT rotated to compensate.

#include <avr/sleep.h>
#include <avr/power.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "clouds.h"

#define TFT_CS   10 // Chip select line for TFT  DO NOT CHANGE
#define TFT_DC    8 // Data/command line for TFT DO NOT CHANGE
#define TFT_RST   6 // TFT Reset pin
#define BACKLIGHT 9 // TFT "Lite" pin
#define EXTRAGND  4 // Extra ground pin for vibration switch
                    // Other leg of vibe switch MUST go to pin 3!

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

#define N_CLOUDS 6

struct {          // Cloud structure:
  uint8_t column; // Screen position 0-3
  uint8_t reps;   // Number of middle tiles in cloud (0-3)
  int16_t y;      // Top edge of cloud * 16 (subpixel pos)
  int16_t endy;   // Reset when Y reaches this value
  int16_t prev;   // Pixel position on prior frame
} cloud[N_CLOUDS];

const uint8_t PROGMEM          // For each of the 4 cloud columns...
  xpos[] = { 4, 36, 68, 100 }, // X pixel coordinate
  inc[]  = { 7, 10, 13,  16 }; // Vertical subpixel speed (16 = 1px)
  // The pseudo-parallax scrolling isn't canon, but adds flair(tm).

uint32_t startTime;

void setup(void) {
  randomSeed(analogRead(2));           // Seed randomness from unused input
  DDRB  = DDRC  = DDRD  = 0x00;        // Set all pins to inputs and
  PORTB = PORTC = PORTD = 0xFF;        // enable pullups (for power saving)
  pinMode(BACKLIGHT, OUTPUT);
  digitalWrite(BACKLIGHT, LOW);        // Backlight off
  pinMode(EXTRAGND, OUTPUT);           // Set one pin low to provide a handy
  digitalWrite(EXTRAGND, LOW);         // ground point for vibration switch

  tft.initR(INITR_144GREENTAB);        // Init 1.44" "green tab" screen
  SPI.setClockDivider(SPI_CLOCK_DIV2); // Force 8 MHz SPI for faster refresh
  // Default rotation (0) is used.  Rotation 3 would be cooler (breakout board
  // would hang symmetrically from mounting holes), but experiencing glitches/
  // artifacts when using non-default rotations on this screen; possible
  // MADCTL/CASET/RASET register strangeness to be resolved in library.
  // So the screen must be mounted with the control pins on the left.
  // tft.setRotation(3);
  tft.fillScreen(0x6C3F);              // Sky background
  // Cloud columns are primed to nonsense value so comparisons in
  // randomize() don't have trouble with non-initialized clouds.
  for(uint8_t i=0; i<N_CLOUDS; i++) cloud[i].column = 255;
  for(uint8_t i=0; i<N_CLOUDS; i++) randomize(i, false);

  // AVR peripherals that aren't used by this code are disabled to further
  // conserve power, and may take certain Arduino functionality with them.
  // If you adapt this code to other projects, may need to re-enable some.
  power_adc_disable();    // Disable ADC (no analogRead())
  power_twi_disable();    // Disable I2C (no Wire library)
  power_usart0_disable(); // Disable UART (no Serial)
  power_timer1_disable();
  power_timer2_disable();

  EICRA = _BV(ISC11); // Falling edge of INT1 (pin 3) generates an interrupt
  EIMSK = _BV(INT1);  // Enable interrupt (vibration switch wakes from sleep)

  digitalWrite(BACKLIGHT, HIGH); // Backlight on
  startTime = millis();
}


// Copy data from tile array to screen, w/some clipping.
// Address window must already be set in calling function.
int16_t blitt(const uint8_t *ptr,    // -> tile data (in clouds.h)
                   int16_t  y) {    // Position (topmost row) on screen
  uint8_t h = pgm_read_byte(ptr++); // Tile height
  int16_t r = y + h;                // Return value = pos. of next tile
  if((y < 128) && (y > -h)) {       // Ignore tile clipped fully off screen
    if(y < 0) {                     // Tile clipped partially off top
      ptr += y * -48;               //  Move data pointer to first visible row
      h   += y;                     //  Reduce blit height
    } else if(r > 128) {            // Tile clipped partially off bottom
      h = 128 - y;                  //  Reduce blit height
    }
    uint16_t count = h * 48;        // Number of bytes to transfer
    uint8_t  c;                     // Temp byte storage
    SPDR = pgm_read_byte(ptr++);    // Issue first byte
    while(--count) {                // Do loop control during SPI out
      c = pgm_read_byte(ptr++);     // Fetch next byte during SPI out
      while(!(SPSR & _BV(SPIF)));   // Wait for SPI completion
      SPDR = c;                     // Issue next byte
    }
    while(!(SPSR & _BV(SPIF)));     // Wait for last byte out
  }
  return r;                         // Starting pos. of next tile
}

void loop() {
  uint32_t t = millis();
  int16_t  y;
  uint8_t  i, x, r;

  for(i=0; i<N_CLOUDS; i++) {                           // For each cloud...
    if((y = (cloud[i].y / 16)) != cloud[i].prev) {      // Has it moved?
      if(y < 128) {                                     // Is it on screen yet?
        x = pgm_read_byte(&xpos[cloud[i].column]);      // Horiz pos from table
        // Address window = blit destination rectangle...
        tft.setAddrWindow(x, (y > 0) ? y : 0, x+23, 127);
        // Access ST7735 control pins directly...dirty hack...
        PORTB |=  _BV(0);                               // Data mode
        PORTB &= ~_BV(2);                               // Chip select
        y = blitt(tile_a, y);                            // Blit first tile of cloud
        for(r=0; r<cloud[i].reps; r++) y = blitt(tile_b, y); // Middle tiles
        blitt(tile_c, y);                                // Last tile
        PORTB |= _BV(2);                                // Chip deselect
      }
      cloud[i].prev = y;                                // Record new position
    }
    cloud[i].y -= pgm_read_byte(&inc[cloud[i].column]); // Move cloud (subpixel)
    if(cloud[i].y < cloud[i].endy) randomize(i, true);  // Regenerate?
  }

  if((t - startTime) >= 15000L) {                       // If 15 seconds elapsed...
    digitalWrite(BACKLIGHT, LOW);                       // Backlight off
    PORTB &= ~(_BV(0) | _BV(2));                        // Command + chip select
    for(SPDR = ST7735_SLPIN; !(SPSR & _BV(SPIF)););     // Issue command
    PORTB |= _BV(2);                                    // Chip deselect
    power_spi_disable();                                // Disable remaining periphs
    power_timer0_disable();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);                // Deepest sleep
    sleep_mode();
    // Execution resumes here on wake.
    power_spi_enable();                                 // Re-enable SPI
    power_timer0_enable();                              // and millis(), etc.
    PORTB &= ~(_BV(0) | _BV(2));                        // Command + chip select
    for(SPDR = ST7735_SLPOUT; !(SPSR & _BV(SPIF)););    // Screen on
    PORTB |= _BV(2);                                    // Chip deselect
    delay(120);                                         // Must pause after wake
    digitalWrite(BACKLIGHT, HIGH);                      // Backlight on
    startTime = millis();
  } else if((t = (millis() - t)) < 30) {
    delay(30 - t);                                      // Regular-ish frame timing
  }
}

// Randomize values for one cloud, making sure it doesn't overlap others
void randomize(uint8_t i, boolean offRight) {
  uint8_t j, tries = 0;
  int     iy1, iy2, jy1, jy2, maxy = 2048;

  cloud[i].reps = random(4);     // # tiles repeated in middle (0-3)
  do {
    cloud[i].column = random(4); // Randomize position...
    cloud[i].y      = 16 * (offRight ? (128 + random(64)) :
                      random((2 + cloud[i].reps) * -16, 192));
    iy1 = cloud[i].y;                             // Top of cloud i
    iy2 = iy1 + (2 + cloud[i].reps) * 256 + 15;   // Bottom of cloud i
    for(j=0; j<N_CLOUDS; j++) { // Then test if it overlaps other clouds...
      if((i == j) || (cloud[i].column != cloud[j].column)) continue;
      jy1 = cloud[j].y;                           // Top of cloud j
      jy2 = jy1 + (2 + cloud[j].reps) * 256 + 15; // Bottom of cloud j
      if(jy2 > maxy) maxy = jy2;                  // Track lowest cloud
      if((jy1 <= iy2) && (jy2 >= iy1)) break;     // Overlap!
    }
  } while((j < N_CLOUDS) && (++tries < 5));       // Retry until no overlap
  if(tries > 4) cloud[i].y = maxy + 16;           // Give up; move to bottom
  cloud[i].endy = (2 + cloud[i].reps) * -256 - 31;
  cloud[i].prev = -30000;
}

ISR(INT1_vect) { } // Vibration switch wakeup interrupt