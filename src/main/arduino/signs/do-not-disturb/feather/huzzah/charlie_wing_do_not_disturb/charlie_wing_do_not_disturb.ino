
#define LED_PIN         2                // Pin connected to the LED.

#include <ESP8266WiFi.h>

void setup() 
{
    Serial.begin(115200);
    delay(10);

    // Setup LED and turn it off.
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // setup the quadalpha dispaly
//    initQuadAlpha();

    // Connect to WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WIFI_NAME);
    
    // Explicitly turn off the Access Point mode, in case it was activated the last time the 
    // esp8266 was programmed.
    WiFi.mode(WIFI_STA);

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
    
//    displayInitMessage();

    message = localhostIp;
}
