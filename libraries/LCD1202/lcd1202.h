#ifndef __LCD1202
#define __LCD1202
#include <Arduino.h>

#if (defined(__AVR__))
#include <avr\pgmspace.h>
#else
#include <pgmspace.h>
#endif

// прототипы функций


class LCD1202 {
  public:
       LCD1202(uint8_t _RES, uint8_t _CS, uint8_t _Data, uint8_t _Clock);
       void Inicialize();
       void Clear_LCD();
       void Update();
       void drawPixel(byte x, byte y, boolean color);
       void fillScreen(boolean color);
       void drawChar(byte x, byte y, boolean color, unsigned char c);
       void print(byte x, byte y, boolean color, char *str);
	   void print(byte x, byte y, boolean color, long num);
	   void print_1607(byte x, byte y, boolean color, char *str);
       void drawLine(byte x0, byte y0, byte x1, byte y1, boolean color);
       void drawFastVLine(byte x, byte y, byte h, boolean color);
       void drawFastHLine(byte x, byte y, byte w, boolean color);
       void drawRect(byte x, byte y, byte w, byte h, boolean color);
       void drawCircle(byte x0, byte y0, int16_t r, boolean color);
       void drawRoundRect(byte x, byte y, byte w, byte h, byte r, boolean color);
       void drawTriangle(byte x0, byte y0, byte x1, byte y1, byte x2, byte y2, boolean color);
       void drawCircleHelper(byte x0, byte y0, byte r, byte cornername, boolean color);
       void fillCircle(byte x0, byte y0, byte r, boolean color);
       void fillCircleHelper(byte x0, byte y0, byte r, byte cornername, byte delta, boolean color);
       void fillRect(byte x, byte y, byte w, byte h, boolean color);
       void fillRoundRect(byte x, byte y, byte w, byte h, byte r, boolean color);
       void fillTriangle(byte x0, byte y0, byte x1, byte y1, byte x2, byte y2, boolean color);
       void drawBitmap(byte x, byte y, const char *bitmap, byte w, byte h, boolean color);
       void simb16x32(byte x, byte y, boolean color, byte c);
       void simb10x16(byte x, byte y, boolean color, byte c);
  private:
       void dWrite(byte pin, byte val);
       void SendByte(byte mode, byte c);
};
#endif
