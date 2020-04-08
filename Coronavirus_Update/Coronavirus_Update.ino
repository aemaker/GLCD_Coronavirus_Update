/*==================================================================================
  ➤ Created by AE Maker - 2020
  ➤ Don’t forget to subscribe to my Youtube channel:
     https://www.youtube.com/AEMaker
  ==================================================================================*/
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "image.h"
#include "corona.h"
#include "lcd1202.h"

char *ssid     = "AE Maker";
char *password = "12345678";


void setup () {
  WiFi.disconnect();
  Serial.begin(115200);
  Serial.println("Coronavirus Update");

  lcd.Inicialize();   // initialize display
  
  connectWifi(ssid, password);
  shiftDisplay();
  delay(5000);
}
 
void loop() {
  char str[16];
  
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    for(int i=0; i<10; i++) {
      coronaUpdate(country_code[i]);
      drawScreen();
      lcd.Update();
      delay(5000);
    }
  }

  delay(1000);
}
