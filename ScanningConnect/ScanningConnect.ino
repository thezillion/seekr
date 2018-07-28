/*
 *  This sketch demonstrates how to scan WiFi networks. 
 *  The API is almost the same as with the WiFi Shield library, 
 *  the most obvious difference being the different file you need to include:
 */
#include "ESP8266WiFi.h"
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  
  WiFi.mode(WIFI_AP_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");

  
}

void loop() {
  
  ConnectSetup();
  // Wait a bit before scanning again
  delay(5000);
}
void ConnectSetup()
{
  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      String ssid =WiFi.SSID(i).substring(0,5);
     
      if(ssid == "SEEKR")
      {
         String StringSSIDP;
         char StringSSID[32]=(char)WiFi.SSID(i); 
         //StringSSIDP=&StringSSID;
          char* BufSSID = (char*)StringSSID;
         
         Serial.println((char*)BufSSID);
         const char* Pass="00000001";
         WiFiMulti.addAP(BufSSID,Pass);
         while(WiFiMulti.run() != WL_CONNECTED) {
         delay(100);
        }
        Serial.println("Connected");
      }
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      Serial.println(ssid);
      delay(10);
    }
  }
  Serial.println("");
}


const char* string2char(String command){
    if(command.length()!=0){
        const char *p = const_cast<char*>(command.c_str());
        return p;
    }
}



