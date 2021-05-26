/*
* Project Name: SSD1306_OLED_RPI
* File: SSD1306_OLED_graphics.h
* Description: header file for the custom graphics functions
* Author: Gavin Lyons.
* URL: https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI
*/

#ifndef _SSD1306_OLED_GRAPHICS_H
#define _SSD1306_OLED_GRAPHICS_H

#include "Print.h"
#include <stdio.h>
#include <stdint.h>
#include "SSD1306_OLED_font.h"


// ****** USER OPTION FONTS ******
// Can be commented out if not needed
#define OLED_Font_One
#define OLED_Font_Two
#define OLED_Font_Three
#define OLED_Font_Four
#define OLED_Font_Five
// ********************************

#ifdef OLED_Font_One
#include "SSD1306_OLED_font.h" // Default 5X8 full extended ASCII
#endif
#ifdef OLED_Font_Two
#include "SSD1306_OLED_font_two.h" // Thick 7X8  (NO LOWERCASE LETTERS)
#endif
#ifdef OLED_Font_Three
#include "SSD1306_OLED_font_three.h" // Seven segment 4X8
#endif
#ifdef OLED_Font_Four
#include "SSD1306_OLED_font_four.h" // Wide  8X8 (NO LOWERCASE LETTERS)
#endif
#ifdef OLED_Font_Five
#include "SSD1306_OLED_font_five.h" // bigNums 16 by 32 1-10 + : . space only
#endif

#define swap(a, b) { int16_t t = a; a = b; b = t; }
// Fonts setup
#define SSD1306_ASCII_OFFSET 0x00
#define SSD1306_ASCII_OFFSET_SP 0x20 // Starts at Space
#define SSD1306_ASCII_OFFSET_NUM 0x2E // Starts at .

class SSD1306_graphics : public Print{

 public:

  SSD1306_graphics(int16_t w, int16_t h); // Constructor

  // This MUST be defined by the subclass:
  virtual void drawPixel(int16_t x, int16_t y, uint16_t color) = 0;

  // These MAY be overridden by the subclass to provide device-specific
  // optimized code.  Otherwise 'generic' versions are used.
  virtual void
	drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color),
	drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color),
	drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color),
	drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color),
	fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color),
	fillScreen(uint16_t color);


  // no subclass overrides
  void
	drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color),
	drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
	  uint16_t color),
	fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color),
	fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
	  int16_t delta, uint16_t color),
	drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
	  int16_t x2, int16_t y2, uint16_t color),
	fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
	  int16_t x2, int16_t y2, uint16_t color),
	drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
	  int16_t radius, uint16_t color),
	fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
	  int16_t radius, uint16_t color),
	drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,
	  uint16_t bg, uint8_t size),
	setCursor(int16_t x, int16_t y),
	setTextColor(uint16_t c),
	setTextColor(uint16_t c, uint16_t bg),
	setTextSize(uint8_t s),
	setTextWrap(bool w),
	setFontNum(uint8_t FontNumber),
	setRotation(uint8_t r);
	
  virtual size_t write(uint8_t);

	void drawCharBigNum(uint8_t x, uint8_t y, uint8_t c, uint16_t color ,uint16_t bg);
	void drawTextBigNum(uint8_t x, uint8_t y, char *pText, uint16_t color, uint16_t bg);
	int16_t height(void) const;
	int16_t width(void) const;
	uint8_t getRotation(void) const;

 protected:
  const int16_t
	WIDTH, HEIGHT;   // This is the 'raw' display w/h - never changes
  int16_t
	_width, _height, // Display w/h as modified by current rotation
	cursor_x, cursor_y;
	 uint16_t
	textcolor, textbgcolor;
	uint8_t textsize;
	uint8_t rotation;
	bool wrap; // If set, 'wrap' text at right edge of display
	uint8_t _FontNumber = 1;
	uint8_t _CurrentFontWidth = 5;
	uint8_t _CurrentFontoffset = 0;
	uint8_t _CurrentFontheight = 8;
};

#endif 
