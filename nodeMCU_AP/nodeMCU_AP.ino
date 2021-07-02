#include <ESP8266WiFi.h>
const char MY_WIFI_SSID[] = "ROBOTIK UNAMA";
const char MY_WIFI_PASSWORD[] = "robotikunama";

WiFiServer server(80);
void setup()
{
  Serial.begin(115200);
  WiFiconfig();
  server.begin();
}
void loop()
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
}
void WiFiconfig()
{
  WiFi.mode(WIFI_AP);
  String WIFIHOTSPOT = MY_WIFI_SSID;
  char WIFIHOTSPOT_CHAR[WIFIHOTSPOT.length() + 1];
  memset(WIFIHOTSPOT_CHAR, 0, WIFIHOTSPOT.length() + 1);
  for (int i = 0; i < WIFIHOTSPOT.length(); i++)
    WIFIHOTSPOT_CHAR[i] = WIFIHOTSPOT.charAt(i);
  WiFi.softAP(WIFIHOTSPOT_CHAR, MY_WIFI_PASSWORD);
}
