
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

/**
 * Setup the touch screen.
 */
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 3800
#define TS_MAXX 100
#define TS_MINY 100
#define TS_MAXY 3750

// Size of the color selection boxes and the paintbrush size
#define BOXSIZE 40
#define PENRADIUS 3
int oldcolor, currentcolor;

void setupTft()
{
    if (!ts.begin()) 
    {
      Serial.println("Couldn't start touchscreen controller");
      while (1);
    }
    Serial.println("Touchscreen started");
    
    tft.begin();
    tft.fillScreen(ILI9341_BLACK);

    // make the color selection boxes
    tft.fillRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_RED);
    tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_YELLOW);
    tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, ILI9341_GREEN);
    tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, ILI9341_CYAN);
    tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, ILI9341_BLUE);
    tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, ILI9341_MAGENTA);

    // select the current color 'red'
    tft.drawRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
    currentcolor = ILI9341_RED;
}