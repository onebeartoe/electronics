
/**
 * This is frin JohnnyDoe's comment on this guide:
 * 
 *      https://www.hackster.io/rayburne/nist-date-time-with-esp8266-e8b9a9
 */


#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <TimeLib.h>

const char *ssid     = "netowrk-name";
const char *password = "lkjlkj";

const long utcOffsetInSeconds = 3600 * 7;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "north-america.pool.ntp.org", utcOffsetInSeconds);

void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();

  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  Serial.println(timeClient.getFormattedTime());

  unsigned long epoch = timeClient.getEpochTime();
  
  Serial.print("year: ");
  Serial.println( year(epoch) );
  
  Serial.print("month: ");
  Serial.println( month(epoch) );
  
  Serial.print("day: ");
  Serial.println( day(epoch) );
  
  delay(10 * 1000);
}