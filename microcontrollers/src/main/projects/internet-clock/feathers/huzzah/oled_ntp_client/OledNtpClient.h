
#ifndef onebeartoe_OledNtpClient_h
#define onebeartoe_OledNtpClient_h

#include "Arduino.h"

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/InternetClock.h"
//#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/InternetClock.cpp"

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/microcontroller/adafruit/feather-wings/oled/src/OledFeatherWing.h"
//#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/microcontroller/adafruit/feather-wings/oled/src/OledFeatherWing.cpp"

class OledNtpClient : public OledFeatherWing
{
    public:

        // override the parent class constructor
        OledNtpClient(Adafruit_SSD1306* display):OledFeatherWing(display){};

        InternetClock* clock;
        
        // override the parent class implementation
        void aButtonPressed()
        {
            Serial.println("hello from subclass!");
            
            oledDisplay->clearDisplay();
            oledDisplay->setCursor(0, 0);
            oledDisplay->setTextSize(4);
            oledDisplay->print(clock->hour);
            oledDisplay->print(":");
            oledDisplay->print(clock->minute);   
        }
        
        void setClock(InternetClock* clock)
        {
            this->clock = clock;
        }
};

#endif
