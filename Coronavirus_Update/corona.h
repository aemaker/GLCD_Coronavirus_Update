/*==================================================================================
  ➤ Created by AE Maker - 2020
  ➤ Don’t forget to subscribe to my Youtube channel:
     https://www.youtube.com/AEMaker
  ==================================================================================*/
#ifndef CORONA_H
#define CORONA_H

#include "lcd1202.h"

#define swap(a, b) { int t = a; a = b; b = t; }

/* LCD */
byte LCD_RAM_BUFF[864];
extern byte LCD_RAM[864];
LCD1202 lcd(2, 0, 4, 5);  // RST, CS, MOSI, SCK

int cases;
int deaths;
int recovered;
char country[16];

String country_code[10] = {"USA", "Italy", "China", "Spain", "Germany", "France", "Iran", "UK", "Switzerland", "S.%20Korea"};

void connectWifi(char *id, char *pwd);
void copyBuffer(void);
void swapBuffer(void);
void shiftBuffer(void);
void shiftDisplay(void);
void drawScreen(void);
bool coronaUpdate(String code);


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

void copyBuffer(void) {
  for(int i = 0; i < 864; i++) {
    LCD_RAM_BUFF[i] = LCD_RAM[i];
  }
}

void swapBuffer(void) {
  for(int i = 0; i < 864; i++) {
    swap(LCD_RAM[i], LCD_RAM_BUFF[i]);
  }
}

void shiftBuffer(void) {
  int cnt=0;
  
  for(int i = 0; i < 864; i++) {
    if(i % 96 == 95) {
      LCD_RAM[i] = LCD_RAM_BUFF[cnt * 96];
      cnt++;
    }
    else  LCD_RAM[i] = LCD_RAM[i + 1];
  }

  for(int i = 0; i < 864; i++) {
    if(i % 96 == 95)  LCD_RAM_BUFF[i] = 0;
    else  LCD_RAM_BUFF[i] = LCD_RAM_BUFF[i + 1];
  }
}

void shiftDisplay(void) {
  copyBuffer();
  coronaUpdate("all");
  drawScreen();
  swapBuffer();
  
  for(int i = 0; i < 96/2; i++) {
    shiftBuffer();
    shiftBuffer();
    lcd.Update();
    delay(1);
  }
}

void drawScreen(void) {
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
}

bool coronaUpdate(String code) {
  HTTPClient http;

  if(code == "all") {
    http.begin("http://coronavirus-19-api.herokuapp.com/all/");
  }
  else  http.begin("http://coronavirus-19-api.herokuapp.com/countries/" + code);
  
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

    if(code == "all") {
      strcpy(country, "Global Virus");
    }
    else {
      strcpy(country, parsed["country"]);
      Serial.print("Country: ");
      Serial.println(country);
    }
  
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
