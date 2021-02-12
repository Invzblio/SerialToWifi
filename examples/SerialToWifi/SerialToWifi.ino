#include <Arduino.h>
#include <WiFi.h>
#include <SerialToWifi.h> // Comment this line to revert to the original Serial behavior

#define SSID "SSID_NAME"
#define PASSWORD "PASSWORD"

#ifdef SERIALTOWIFI
  #define SERVER  "YOUR_HOST_IP_ADDRESS"
  #define SERVER_PORT 6767
  SerialToWifi serialToWifi(SERVER, SERVER_PORT, TIMESTAMP|NO_RECONNECT);
  // TIMESTAMP: Displays a timestamp at the beginning of each line
  // NO_RECONNECT: Will not try to reconnect if the host is unreachable at some point. A reset is required to restart debug outputs.	
#endif 


void startWifi()
{
  // launch WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    //Connection Failed! Stop ...
    while (1)
      delay(1000);
  }
}



void setup() 
{
  // Wifi must be started first
  // Since we're relying on wifi for serial monitoring, Serial.prints won't be visible until it is started.
  startWifi();

  Serial.begin(115200);
  Serial.println("Starting");

  Serial.println("Sending values 0-9 on different lines");
  for (int x = 0; x < 10; x++)
  {
      Serial.println(x);
  }
  Serial.println("Please enter a string in the console, it will be echoed immediately");
}

void loop() 
{
  // Check for data and echo it back to the console.
  if (Serial.available())
  {
    String s;
    s = Serial.readStringUntil(' ');
    Serial.println(s);
  }
  delay(10);
}
