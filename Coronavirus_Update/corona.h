/*==================================================================================
  ➤ Created by AE Maker - 2020
  ➤ Don’t forget to subscribe to my Youtube channel:
     https://www.youtube.com/AEMaker
  ==================================================================================*/
#ifndef CORONA_H
#define CORONA_H

#include "lcd1202.h"

LCD1202 lcd(2, 0, 4, 5);  // RST, CS, MOSI, SCK

int cases;
int deaths;
int recovered;
char country[16];

String country_code[10] = {"China", "Italy", "USA", "Spain", "Germany", "Iran", "France", "S.%20Korea", "Switzerland", "UK"};


void connectWifi(char *id, char *pwd) {
  int cnt=0;
  
  lcd.Clear_LCD();  // clear the display
  lcd.drawBitmap(0, 0, earth, 96, 64, 1);  // draw World Map
  lcd.Update();  // update the display

  Serial.print("Connectingto wifi ");
    
  WiFi.mode(WIFI_STA);
  WiFi.begin(id, pwd);
  
  while(WiFi.status() != WL_CONNECTED) {
    lcd.drawCircle(38, 64, 1, (cnt == 0) ? 0 : 1);    lcd.drawCircle(38, 64, 2, (cnt == 0) ? 1 : 0);
    lcd.drawCircle(48, 64, 1, (cnt == 1) ? 0 : 1);    lcd.drawCircle(48, 64, 2, (cnt == 1) ? 1 : 0);
    lcd.drawCircle(58, 64, 1, (cnt == 2) ? 0 : 1);    lcd.drawCircle(58, 64, 2, (cnt == 2) ? 1 : 0);
    lcd.Update();
    delay(500);
    Serial.print(".");

    (cnt == 2) ? cnt = 0 : cnt++;
  }
//  lcd.Clear_LCD();
  lcd.print(20, 60, 1, "CONNECTED");
  lcd.Update();
  
  Serial.println("\tCONNECTED\n");
}

bool coronaUpdate(String code) {
  HTTPClient http;

  http.begin("http://coronavirus-19-api.herokuapp.com/countries/" + code);
  
  int httpCode = http.GET();  //Send the request
  if (httpCode > 0) {
    String payload = http.getString();  //Get the request response payload
    Serial.println(payload);  //Print the response payload

    StaticJsonBuffer<512> JSONBuffer;   //Memory pool
    JsonObject& parsed = JSONBuffer.parseObject(payload); //Parse message
    
    if (!parsed.success()) {   //Check for errors in parsing
      Serial.println("Parsing failed");
      delay(5000);
      return false;
    }
    
    strcpy(country, parsed["country"]);
    Serial.print("Country: ");
    Serial.println(country);

    cases = parsed["cases"];
    Serial.print("Cases: ");
    Serial.println(cases);
    
    deaths = parsed["deaths"];
    Serial.print("Deaths: ");
    Serial.println(deaths);
    
    recovered = parsed["recovered"];
    Serial.print("Recovered: ");
    Serial.println(recovered);
    Serial.println();

    http.end();
    return true;
  }
}


#endif
