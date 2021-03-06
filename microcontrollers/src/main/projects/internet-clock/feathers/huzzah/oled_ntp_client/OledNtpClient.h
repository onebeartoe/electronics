
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
        
        int previousMinute = 0;

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
            
            String hour = "";
            if(clock->hour < 10)
            {
                hour += "0";
            }
            hour += clock->hour;
            
            String minute = "";            
            if(clock->minute < 10)
            {
                minute += "0";
            }            
            minute += clock->minute;
            
            oledDisplay->print(hour);
            oledDisplay->print(":");
            oledDisplay->print(minute);
        }
        
        /**
         * override the main loop
         */
        void oneLoop()
        {
            // call the parent version of this method
            OledFeatherWing::oneLoop();
            
            if(previousMinute != clock->minute)
            {
                aButtonPressed();
                
                previousMinute = clock->minute;
            }
        } 
        
        void setClock(InternetClock* clock)
        {
            this->clock = clock;
        }
};

#endif
