
/**
 * This was originally from the video, "Raspberry Pi Talking To WiFi Things Part 3"
 *
 *     https://www.youtube.com/watch?v=4K-0iQBalfs
 *
 * This is the source code
 *
 *     https://github.com/adafruit/Raspberry_Pi_Talk_To_Things/tree/master/Part_3
 */

// Raspberry Pi Talking To WiFi Things Part 3
// Use a push button connected to an ESP8266 to toggle a LED on a Raspberry Pi
// on and off, and a push button connected to Pi to toggle a LED on the ESP8266
// on and off.  A special Python server must be running on the Pi and it will listen
// for LED toggle commands from the ESP8266 and send LED toggle commands when its
// button is pressed.
// Author: Tony DiCola
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

// Configuration:
#define WIFI_NAME       "beto-land-0"  // Your WiFi AP.

/**
 * !!!!! DO NOT COMMIT THE REA PASSWORD!!!!!jhg
 */
#define WIFI_PASSWORD   "w" // Your WiFi AP password.
#define LED_PIN         2                // Pin connected to the LED.
#define BUTTON_PIN      0                // Pin connected to the button.
#define SERVER_PORT     5000             // Port the server will listen for connections.

#define SERVER_NAME     "esp8266-NOTNOTNOT-text"  // mDNS name to use for the server.




#define PI_ADDRESS      "192.168.1.133"   // IP address (or hostname) of the Raspberry Pi
// to connect to and toggle its LED on button press.


String localhostIp;

// Create an instance of the server listening on the server port.
WiFiServer server(SERVER_PORT);

void displayInitMessage()
{
    alpha4.clear();

    alpha4.writeDigitAscii(0, 'R');
    alpha4.writeDigitAscii(1, 'I');
    alpha4.writeDigitAscii(2, 'G');
    alpha4.writeDigitAscii(3, 'T');

    alpha4.writeDisplay();    
}

WiFiClient client;

void handleClient()
{
    // Read a line of input.
    // Use a simple character buffer instead of Arduino's String class
    // because String uses dynamic memory which can be problematic with low
    // memory chips.
    #define RECEIVED_SIZE 11
    char received[RECEIVED_SIZE] = {0};
    
    if (client.readBytesUntil('\n', received, RECEIVED_SIZE - 1) == 0) 
    {
        // Exceeded 1 second timeout waiting for data.
        // Send the client an error and then disconnect them by starting the
        // loop over again (which will clean up and close the client connection).
        client.println("ERROR: Timeout!");
        client.flush();
        return;
    }

    // Match the command.
    if (strncmp(received, "toggle_led", 10) == 0) 
    {
        // Toggle the LED.
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
        Serial.println("Toggle LED!");
    } 
    else 
    {
        // Unknown command, send an error and exit early to close the connection.
        client.print("ERROR: Unknown command: ");
        client.println(received);
        client.flush();
        return;
    }

    // Client will automatically be disconnected at the end of the loop!
    // Call flush to make sure any queued up data finishes sending to the client.
    client.flush();
}



void loop() 
{
    // Check if a client has connected.
    client = server.available();
    if (!client) 
    {
        // No client connected, start the loop over again.
        return;
    }
    else
    {
        handleClient();
    }
}

void initQuadAlpha() 
{
    // pass in the address
    alpha4.begin(0x70);


    alpha4.clear();

    alpha4.writeDigitAscii(0, '7');
    alpha4.writeDigitAscii(1, 'I');
    alpha4.writeDigitAscii(2, 'C');
    alpha4.writeDigitAscii(3, 'E');

    alpha4.writeDisplay();

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
    Serial.println(WIFI_NAME);

    WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

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
    Serial.println(localhostIp);

    // Setup mDNS responder.
    if (!MDNS.begin(SERVER_NAME)) 
    {
        Serial.println("Error setting up MDNS responder!");
        while (1) 
        {
            delay(1000);
        }
    }
    
    displayInitMessage();
}