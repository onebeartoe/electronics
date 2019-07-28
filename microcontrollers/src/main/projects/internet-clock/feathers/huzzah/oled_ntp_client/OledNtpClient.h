
#ifndef onebeartoe_OledNtpClient_h
#define onebeartoe_OledNtpClient_h

//#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/InternetClock.h"
//#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/projects/internet-clock/src/InternetClock.cpp"

#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/microcontroller/adafruit/feather-wings/oled/src/OledFeatherWing.h"
//#include "/home/roberto/Versioning/owner/github/onebeartoe/electronics/microcontrollers/src/main/microcontroller/adafruit/feather-wings/oled/src/OledFeatherWing.cpp"

class OledNtpClient : public OledFeatherWing
{
    public:
  
        OledNtpClient(Adafruit_SSD1306* display):OledFeatherWing(display){};
//        OledNtpClient(Adafruit_SSD1306* display);
};


#endif
