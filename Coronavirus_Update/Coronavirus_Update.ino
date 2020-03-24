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

const char *ssid     = "TP-LINK_ACB8";
const char *password = "99021399";


void setup () {
  Serial.begin(115200);
  Serial.println("Coronavirus Update");

  lcd.Inicialize();   // initialize display
  
  connectWifi((char*)ssid, (char*)password);
  delay(1000);
}
 
void loop() {
  char str[16];
  
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    for(int i=0; i<10; i++) {
    coronaUpdate(country_code[i]);
    
    lcd.Clear_LCD();
    lcd.drawRect(0, 0, 96, 68, 1);
    lcd.fillRect(0, 0, 96, 11, 1);
    lcd.print(48 - (strlen(country) * 3), 2, 0, country);
    lcd.print(2, 20, 1, "Cases");
    lcd.print(2, 35, 1, "Deaths");
    lcd.print(2, 50, 1, "Recovered");
    lcd.print(59, 20, 1, cases);
    lcd.print(59, 35, 1, deaths);
    lcd.print(59, 50, 1, recovered);
    lcd.Update();
    delay(5000);
    }
  }
}
