
/**
 * 
 * The default IP of the access point is 
 * 
 *      192.168.4.1
 * 
 *      Here is some documentation on changing the default IP address of the 
 *      access point.
 * 
 * This ESP8266 specific source code was originally from Sparkfun's example here
 *
 *        https://learn.sparkfun.com/tutorials/esp8266-thing-hookup-guide/example-sketch-ap-web-server
 * 
 */

#include <ESP8266WiFi.h>

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

//#include "scrolling_text.h"

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

//////////////////////
// WiFi Definitions //
//////////////////////
const char WiFiAPPSK[] = "lovelovelove";

/////////////////////
// Pin Definitions //
/////////////////////
const int LED_PIN = 5; // Thing's onboard, green LED
const int ANALOG_PIN = A0; // The only analog pin on the Thing
const int DIGITAL_PIN = 12; // Digital pin to be read

WiFiServer server(80);

String localhostIp;

int indecies[] = {0,1,2,3};

String message = "Go Spurs Go   *   ";

/**
  * This array holds the current values of the 4 alphanumeric segments.
  */
char displaybuffer[] = {' ', ' ', ' ', ' '};

unsigned long lightPreviousMillis = 0;

unsigned long currentMillis;

/**
 * This is the delay in milliseconds for the scrolling text.
 */
long scrollDelay = 350;

/**
 * 
 * This function is from this answer:
 * TODO: up vote this answer, didn't have have enough rep when I found it.
 *      http://arduino.stackexchange.com/questions/18007/simple-url-decoding/18008#18008?newreg=ee1a83d387c14220befe297697ca7e88
 * 
 * @param input
 * @return 
 */
String decodeRequest(String input)
{
    int arraySize = 50;
    char data[arraySize];
    
    input.toCharArray(data, arraySize);

    // Create two pointers that point to the start of the data
    char *leader = data;
    char *follower = leader;

    // While we're not at the end of the string (current character not NULL)
    while (*leader) {
        // Check to see if the current character is a %
        if (*leader == '%') {

            // Grab the next two characters and move leader forwards
            leader++;
            char high = *leader;
            leader++;
            char low = *leader;

            // Convert ASCII 0-9A-F to a value 0-15
            if (high > 0x39) high -= 7;
            high &= 0x0f;

            // Same again for the low byte:
            if (low > 0x39) low -= 7;
            low &= 0x0f;

            // Combine the two into a single byte and store in follower:
            *follower = (high << 4) | low;
        } else {
            // All other characters copy verbatim
            *follower = *leader;
        }

        // Move both pointers to the next character:
        leader++;
        follower++;
    }
    // Terminate the new string with a NULL character to trim it off
    *follower = 0;
    
    String output(data);
    
    return output;
}

void handleHttpClient()
{
    // Check if a client has connected
    WiFiClient client = server.available();
    if(client) 
    {
        // Read the first line of the request
        String req = client.readStringUntil('\r');
        Serial.println(req);

        // skip the HTTP requests for the favicon.ico
        char * faviconTarget = "GET /favicon.i";
        int index = req.indexOf(faviconTarget);
        
        if(index == -1)
        {
            // the request was not for the favicon
            
            // ignore requests with less than 3 characters in length
            String temp = req.substring(5) + "";
            if(temp.length() < 3)
            {
                Serial.println("invalid message");
            }
            else
            {
                // remove the HTTP request version
                int i = temp.indexOf(" HTTP/1.1");
                if(i >= 0)
                {
                    Serial.println("http header found");
                    temp = temp.substring(0, i) + "";
                }
                else
                {
                    Serial.println("HTTP HEADER not found");
                }
                
                // remove HTTP encoded characters
                temp = decodeRequest(temp);
                
                message = temp;
            }
            
            Serial.println();
            Serial.println("Message was set from an HTTP request: >" + message + "<");
            
            
        }
        else
        {
            Serial.println();
            Serial.println("skipping request for the favorite icon");
        }

        // Prepare the response. Start with the common header:
        String s = "HTTP/1.1 200 OK\r\n";
        s += "Content-Type: text/html\r\n\r\n";
        s += "<!DOCTYPE HTML>\r\n<html>\r\n";
        
        s += "A request was received: >" + req + "<";
        
        s += "</html>\n";

        // Send the response to the client
        client.print(s);
        client.flush();
        
        delay(1);
        Serial.println("Client disconnected");
    }
}

void setup() 
{    
    Serial.begin(115200);
    
    initHardware();
    setupWiFi();
  
    // start the server
    server.begin();
    Serial.println("Server started");

    localhostIp = WiFi.localIP().toString();

    // Print the IP address
    Serial.println();
    Serial.print("local IP: ");
    Serial.println(localhostIp);
    Serial.println();
}

void loop() 
{
    currentMillis = millis();
    
    if(currentMillis - lightPreviousMillis >= scrollDelay) 
    {
        // save the last time you blinked the LED
        lightPreviousMillis = currentMillis;

        updateDisplay();
    }     
    
    handleHttpClient();
}

void setupWiFi()
{
    WiFi.mode(WIFI_AP);

  // Do a little work to get a unique-ish name. Append the
  // last two bytes of the MAC (HEX'd) to "Thing-":
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = "ESP8266 Scroller " + macID;

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, WiFiAPPSK);
}

void initHardware()
{
  
  pinMode(DIGITAL_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  // Don't need to set ANALOG_PIN as input, 
  // that's all it can be.

    initQuadAlpha();
}

void initQuadAlpha()
{
    // pass in the address
    alpha4.begin(0x70);  

  
    alpha4.clear();

    alpha4.writeDigitAscii(0, 'N');
    alpha4.writeDigitAscii(1, 'I');
    alpha4.writeDigitAscii(2, 'C');
    alpha4.writeDigitAscii(3, 'E');

    alpha4.writeDisplay();
   
    Serial.println("The Adafruit_AlphaNum4 setup is complete.");
}

void updateDisplay()
{
    // shift the index into the message for each segment 
    indecies[0] += 1;
    indecies[1] += 1;
    indecies[2] += 1;
    indecies[3] += 1;

    if(indecies[0] == message.length())
    {
        indecies[0] = 0;
    }

    if(indecies[1] == message.length())
    {
        indecies[1] = 0;
    }

    if(indecies[2] == message.length())
    {
        indecies[2] = 0;
    }

    if(indecies[3] == message.length())
    {
        indecies[3] = 0;
    }
  
  // scroll down display
  displaybuffer[0] = message[indecies[0]];
  displaybuffer[1] = message[indecies[1]];
  displaybuffer[2] = message[indecies[2]];
  displaybuffer[3] = message[indecies[3]];
 
  // set every digit to the buffer
  alpha4.writeDigitAscii(0, displaybuffer[0]);
  alpha4.writeDigitAscii(1, displaybuffer[1]);
  alpha4.writeDigitAscii(2, displaybuffer[2]);
  alpha4.writeDigitAscii(3, displaybuffer[3]);
 
  // write it out!
  alpha4.writeDisplay();    
}
