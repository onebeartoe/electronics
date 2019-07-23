
// https://learn.adafruit.com/7-segment-display-internet-clock#code


//##########################################################################
// FeatherClock - Use the Adafruit seven segment LED FeatherWing to display
// the current time, which we fetch from the Internet using NTP. This
// program assumes the seven segment display is attached to a Feather M0
// WiFi (WINC1500).
//
// At the top of every hour, re-sync with NTP to correct for any drift.
//
// Credit: This is based heavily on the work by Tony DiCola from Adafruit.
// Suggest (strongly) you go to adafruit.com and buy some product from
// them. WINC1500 code modified from example code provided by Michael
// Margolis and Tom Igoe.
//
// Philip R. Moyer
// Adafruit
//
// This source code is released under the BSD license.
// Any further redistribution must include this header.
//##########################################################################

//##########################################################################
// Includes and defines
//##########################################################################

#include <SPI.h>                    // SPI interface API

//#include <Wire.h>                   // Wire support library
//#include <WiFi101.h>                // Wireless header
//#include <WiFiUdp.h>                // UDP support

#include <Adafruit_LEDBackpack.h>   // Support for the Backpack FeatherWing
#include <Adafruit_GFX.h>           // Adafruit's graphics library
#include <Adafruit_SSD1306.h>       // OLED support library

#define WINC_CS       8             // WINC1500 Chip Select
#define WINC_IRQ      7             // WINC1500 interrupt request line
#define WINC_RST      4             // WINC1500 reset line
#define WINC_EN       2             // WINC1500 enable

#define OLED_RESET    3             // OLED reset pin

#define VBATPIN       9             // Pin to read battery voltage

//##########################################################################
// Globals
//##########################################################################

#define TIME_24_HOUR    true
#define DISPLAY_ADDRESS 0x70

// Create display object
Adafruit_7segment clockDisplay = Adafruit_7segment();

int hours = 0;                      // Track hours
int minutes = 0;                    // Track minutes
int seconds = 0;                    // Track seconds
int tzOffset = -4;                  // Time zone offset (-4 = US Eastern time)

bool blinkColon = false;            // Track colon status to blink once/sec

int status = WL_IDLE_STATUS;        // WINC1500 chip status
char ssid[] = "YOUR_SSID";          // WiFi network SSID
char pass[] = "YOUR_WIFI_PASSWORD"; // WiFi password (NOTE: redact before doing a git push!!!)

unsigned int localPort = 2390;      // Local port to listen for UDP packets
IPAddress timeServer(129,6,15,28);  // time.nist.gov NTP server
const int NTP_PACKET_SIZE = 48;     // NTP time stamp is in the first 48 bytes
byte packetBuffer[NTP_PACKET_SIZE]; // Buffer for incoming and outgoing UDP packets

WiFiUDP Udp;                        // Set up a WINC1500 client session

Adafruit_SSD1306 display(128, 32, &Wire, OLED_RESET); // Instantiate OLED object

//##########################################################################
// Functions
//##########################################################################

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address)
{
  //Serial.println("1");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  //Serial.println("2");
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  //Serial.println("3");

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  //Serial.println("4");
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  //Serial.println("5");
  Udp.endPacket();
  //Serial.println("6");
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void printData() {
  float measuredvbat = analogRead(VBATPIN);

  measuredvbat *= 2;      // we divided by 2, so multiply back
  measuredvbat *= 3.3;    // Multiply by 3.3V, our reference voltage
  measuredvbat /= 1024;   // convert to voltage

  display.clearDisplay();
  display.setCursor(0,0);
  display.print("VBat: ");
  display.print(measuredvbat);
  display.println(" volts");
  display.display();
}

//##########################################################################
// Setup - main
//##########################################################################

// This is one of the two standard functions for every Arduino program,
// with the other being loop(). This one runs once at the beginning of the
// program execution and is ordinarily used to initialize hardware and
// variables.

void setup() {
#ifdef WINC_EN
  pinMode(WINC_EN, OUTPUT);
  digitalWrite(WINC_EN, HIGH);
#endif

  WiFi.setPins(WINC_CS, WINC_IRQ, WINC_RST, WINC_EN);

  Serial.begin(115200);                      // Start the serial console
  Serial.println("Clock starting!");         // Start the clock message.

  // Make sure we have WiFi hardware, or there's no point continuing.
  if (WiFi.status() == WL_NO_SHIELD) {
    while (true);                            // Spin loop
  }

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer.
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  // Now back to the setup

  // Set up the display.
  clockDisplay.begin(DISPLAY_ADDRESS);

  // Attempt to conect to the WiFi network.
  Serial.println("Connecting to WiFi netowrk.");
  while (WiFi.status() != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);         // Connect to WPA2 network
    uint8_t timeout = 10;                    // Set a timeout variable
    while (timeout && (WiFi.status() != WL_CONNECTED)) {
      timeout--;                             // Decrement timeout
      delay(1000);                           // Delay for one second
    }
  }

  Serial.println("Connected to network.");
  printWiFiStatus();                         // Display WiFi status data

  Udp.begin(localPort);                      // Open the UDP port for comms
}

//##########################################################################
// Loop - main
//##########################################################################

// This is one of the two standard functions for every Arduino program,
// with the other being setup(). This one runs continuously, forever, and
// executes the Arduino program code.

void loop() {
  // Refresh the time at the top of every hour, or every five minutes
  // because the clock drift on the bare Feather M0 is pretty wicked.
  if ((minutes == 0) || ((minutes % 5) == 0)) {
    sendNTPpacket(timeServer); // send an NTP packet to a time server
    // wait to see if a reply is available
    delay(1000);
    if ( Udp.parsePacket() ) {
      Serial.println("packet received");
      // We've received a packet, read the data from it
      Udp.read(packetBuffer, NTP_PACKET_SIZE); // read packet into buffer

      //the  timestamp starts at byte 40 of the received packet and is four
      // bytes, or two words, long. First, esxtract the two words:

      unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
      unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
      // combine the four bytes (two words) into a long integer
      // this is NTP time (seconds since Jan 1 1900):
      unsigned long secsSince1900 = highWord << 16 | lowWord;
      Serial.print("Seconds since Jan 1 1900 = " );
      Serial.println(secsSince1900);

      // now convert NTP time into everyday time:
      Serial.print("Unix time = ");
      // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
      const unsigned long seventyYears = 2208988800UL;
      // subtract seventy years:
      unsigned long epoch = secsSince1900 - seventyYears;
      // print Unix time:
      Serial.println(epoch);

      // print the hour, minute and second:
      Serial.print("The UTC time is ");   // UTC is the time at Greenwich Meridian (GMT)
      hours = ((epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
      hours += tzOffset;                  // Calculate the time zone offset
      if (hours < 0) {
        hours = 24 + hours;
      }
      if (hours > 23) {
        hours = hours - 23;
      }
      Serial.print(hours); // print the hour
      Serial.print(':');
      minutes = ((epoch % 3600) / 60);
      if (minutes < 10 ) {
        // In the first 10 minutes of each hour, we'll want a leading '0'
        Serial.print('0');
      }
      Serial.print(minutes);  // print the minute (3600 equals secs per minute)
      Serial.print(':');
      seconds = (epoch % 60);  // print the second
      if ( seconds < 10 ) {
        // In the first 10 seconds of each minute, we'll want a leading '0'
        Serial.print('0');
      }
      Serial.println(seconds);
    }
  }
  // Display the time
  int displayValue = hours*100 + minutes;

  if (!TIME_24_HOUR) {
    if (hours > 12) {
      displayValue -= 1200;
    }
    else if (hours == 0) {
      displayValue += 1200;
    }
  }

  // Print the time on the display
  clockDisplay.print(displayValue, DEC);

  // Add zero padding when in 24 hour mode and it's midnight.
  // In this case the print function above won't have leading 0's
  // which can look confusing.  Go in and explicitly add these zeros.
  if (TIME_24_HOUR && hours == 0) {
    // Pad hour 0.
    clockDisplay.writeDigitNum(1, 0);
    // Also pad when the 10's minute is 0 and should be padded.
    if (minutes < 10) {
      clockDisplay.writeDigitNum(2, 0);
    }
  }

  // Blink the colon by flipping its value every loop iteration
  // (which happens every second).
  blinkColon = !blinkColon;
  clockDisplay.drawColon(blinkColon);

  // Now push out to the display the new values that were set above.
  clockDisplay.writeDisplay();

  // Pause for a second for time to elapse.  This value is in milliseconds
  // so 1000 milliseconds = 1 second.
  delay(1000);

  // Now increase the seconds by one.
  seconds += 1;
  // If the seconds go above 59 then the minutes should increase and
  // the seconds should wrap back to 0.
  if (seconds > 59) {
    seconds = 0;
    minutes += 1;
    // Again if the minutes go above 59 then the hour should increase and
    // the minutes should wrap back to 0.
    if (minutes > 59) {
      minutes = 0;
      Serial.println("Minutes set to zero - should query NTP on next loop()");
      hours += 1;
      // Note that when the minutes are 0 (i.e. it's the top of a new hour)
      // then the start of the loop will read the actual time from NTP
      // again.  Just to be safe though we'll also increment the hour and wrap
      // back to 0 if it goes above 23 (i.e. past midnight).
      if (hours > 23) {
        hours = 0;
      }
    }
  }
  printData();  // Display battery voltage on the OLED
}
