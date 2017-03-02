
// do not distrub URL: http://192.168.1.64:5000/do-not-disturb
//        disturb URL: http://192.168.1.64:5000/please-disturb

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

// The next two commented lines are configuration with actutal values 
// in the header (info.h) file outside of the project source code.
#include "C:\home\owner\workspace\arduino\sensitive.h"
//const char* wifi_ssid     = "beto-landia-105";
//const char* wifi_password = "!!!CORRECT-ME!!!";

#define LED_PIN         2                // Pin connected to the LED.
#define BUTTON_PIN      0                // Pin connected to the button.
#define SERVER_PORT     5000             // Port the server will listen for connections.

// mDNS name to use for the server.
#define SERVER_NAME "esp8266-NOTNOTNOT-text"  

String localhostIp;

// Create an instance of the server listening on the server port.
WiFiServer server(SERVER_PORT);

unsigned long currentMillis;

unsigned long lightPreviousMillis = 0;

WiFiClient client;

String message = "";

/**
  * This array holds the current values of the 4 alphanumeric segments.
  */
char displaybuffer[] = {' ', ' ', ' ', ' '};

int indecies[] = {0,1,2,3};

void handleHttpClient()
{
    alpha4.writeDigitAscii(0, 'H');
    alpha4.writeDigitAscii(1, 'i');
    alpha4.writeDigitAscii(2, 't');
    alpha4.writeDigitAscii(3, '!');
    alpha4.writeDisplay();
    delay(250);
    alpha4.clear();
    alpha4.writeDisplay();

    // Read a line of input.
    // Use a simple character buffer instead of Arduino's String class
    // because String uses dynamic memory which can be problematic with low
    // memory chips.
    #define RECEIVED_SIZE 50
    char received[RECEIVED_SIZE] = {0};
    
//    Serial.printf("arg count: %d", client.args() );
    
    if (client.readBytesUntil('\n', received, RECEIVED_SIZE - 1) == 0) 
    {
        // Exceeded 1 second timeout waiting for data.
        // Send the client an error and then disconnect them by starting the
        // loop over again (which will clean up and close the client connection).
        client.println("ERROR: Timeout!");
    }
    else
    {
        char * faviconTarget = "GET /favicon.ico";
        char * targetFound = strstr(received, faviconTarget);
        
        if(targetFound != '\0')
        {
            String s = "skipping request for the favorite icon: " + String(targetFound);
            Serial.println();
            Serial.println(s);
            client.println(s);
        }
        else
        {
// TODO            
            // URL decode the received message
            // like this 
            //         http://arduino.stackexchange.com/questions/18007/simple-url-decoding/18008#18008?newreg=ee1a83d387c14220befe297697ca7e88
                        
            Serial.println();
            Serial.println("received over HTTP: ");
            Serial.println(received);

            // Match the command.
            String s(received);
            if( s.indexOf("do-not-disturb") >= 0)
            {
                message = "Do not Disturb   -   ";
                client.println(message);
            }
            else if(s.indexOf("please-disturb") >= 0)
            {
                message = "   Disturb   -";
                client.println(message);
            }
            else 
            {
                message = received;
                
                // Unknown command, send an error and exit early to close the connection.
                client.print("ERROR: Unknown command : ");
                client.println(received);
            }            
        }
    }

    // Client will automatically be disconnected at the end of the loop!
    // Call flush to make sure any queued up data finishes sending to the client.
    client.flush();
}

/**
 * This is the delay in milliseconds for the scrolling text.
 */
long scrollDelay = 350;

void loop() 
{
    currentMillis = millis();
    
    if(currentMillis - lightPreviousMillis >= scrollDelay) 
    {
        // save the last time you blinked the LED
        lightPreviousMillis = currentMillis;

        updateDisplay();
    }
    
    // Check if a client has connected.
    client = server.available();
    if (client) 
    {
        handleHttpClient();
    }
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
    
    delay(250);

    Serial.println("The Adafruit_AlphaNum4 setup is complete.");
}

void setup() 
{
    Serial.begin(115200);
    delay(10);

    // Setup LED and turn it off.
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // Setup button as an input with internal pull-up.
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // setup the quadalpha dispaly
    initQuadAlpha();

    // Connect to WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(wifi_ssid);
    
    // Explicitly turn off the Access Point mode, in case it was activated the last time the 
    // esp8266 was programmed.
    WiFi.mode(WIFI_STA);

    WiFi.begin(wifi_ssid, wifi_password);

    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");

    // Start the server
    server.begin();
    Serial.println("Server started");

    localhostIp = WiFi.localIP().toString();

    // Print the IP address
    Serial.println();
    
    Serial.print("local IP: ");
    Serial.println(localhostIp);
    Serial.println();

    // Setup mDNS responder.
    if (!MDNS.begin(SERVER_NAME)) 
    {
        Serial.println("Error setting up MDNS responder!");
        while (1) 
        {
            delay(1000);
        }
    }

    message = localhostIp;
}

void updateDisplay()
{
    // shift the index into the message for each segment 
    indecies[0] += 1;
    indecies[1] += 1;
    indecies[2] += 1;
    indecies[3] += 1;

    if(indecies[0] == message.length() )
    {
        indecies[0] = 0;
    }

    if(indecies[1] == message.length() )
    {
        indecies[1] = 0;
    }

    if(indecies[2] == message.length() )
    {
        indecies[2] = 0;
    }

    if(indecies[3] == message.length() )
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
