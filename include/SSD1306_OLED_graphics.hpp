 /*!
	@file SSD1306_OLED_graphics.hpp
	@brief OLED driven by SSD1306 controller. header file
		for the graphics  based functions.
	@details Project Name: SSD1306_OLED_RPI
		URL: https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI
	@author  Gavin Lyons
*/

#pragma once

#include <stdio.h>
#include <stdint.h>
#include <cmath> // for "abs"
#include "SSD1306_OLED_Print.hpp"
#include "SSD1306_OLED_font.hpp"

#define swapOLEDRPI(a, b) { int16_t t = a; a = b; b = t; }

/*! @brief Graphics class to hold graphic related functions */
class SSD1306_graphics : public Print{

 public:

	SSD1306_graphics(int16_t w, int16_t h); // Constructor

	// Graphic related member functions 
	virtual void drawPixel(int16_t x, int16_t y, uint8_t color) = 0;

	void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color);
	void drawFastVLine(int16_t x, int16_t y, int16_t h, uint8_t color);
	void drawFastHLine(int16_t x, int16_t y, int16_t w, uint8_t color);
	void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
	void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
	void fillScreen(uint8_t color);
	void drawCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color);
	void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
	  uint8_t color);
	void fillCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color);
	void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
	  int16_t delta, uint8_t color);
	void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
	  int16_t x2, int16_t y2, uint8_t color);
	void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
	  int16_t x2, int16_t y2, uint8_t color);
	void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
	  int16_t radius, uint8_t color);
	void fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
	  int16_t radius, uint8_t color);

	// Screen related member functions 
	void setCursor(int16_t x, int16_t y);
	void setRotation(uint8_t r);
	int16_t height(void) const;
	int16_t width(void) const;
	uint8_t getRotation(void) const;
	
	// Text & font related member functions 
	virtual size_t write(uint8_t);
	void drawCharBigFont(uint8_t x, uint8_t y, uint8_t c, uint8_t color ,uint8_t bg);
	void drawTextBigFont(uint8_t x, uint8_t y, char *pText, uint8_t color, uint8_t bg);
	void drawText(uint8_t x, uint8_t y, char *pText, uint8_t color, uint8_t bg, uint8_t size);
	void drawChar(int16_t x, int16_t y, unsigned char c, uint8_t color,
	  uint8_t bg, uint8_t size);
	void setTextColor(uint8_t c);
	void setTextColor(uint8_t c, uint8_t bg);
	void setTextSize(uint8_t s);
	void setTextWrap(bool w);
	void setFontNum(OLEDFontType_e FontNumber);

 protected:
	
	const int16_t WIDTH;  /**< This is the 'raw' display w - never changes */
	const int16_t HEIGHT;  /**< This is the 'raw' display h - never changes*/
	int16_t _width;  /**< Display w as modified by current _rotation*/
	int16_t _height;  /**< Display h as modified by current _rotation*/
	int16_t _cursor_x; /**< Current X co-ord cursor position */
	int16_t _cursor_y;  /**< Current Y co-ord cursor position */
	uint8_t _rotation; /**< Current rotation 0-3 */
	
	uint8_t _textcolor;  /**< Text foreground color */
	uint8_t _textbgcolor;   /**< Text background color */
	uint8_t   _textsize = 1; /**< Size of text ,fonts 1-6 */
	bool _textwrap;          /**< If set, '_textwrap' text at right edge of display*/
	uint8_t _FontNumber = 1;                /**< Holds current font number */
	uint8_t _CurrentFontWidth = 5;        /**<Holds current font width in bits */
	uint8_t _CurrentFontoffset = 0x00;  /**<Holds current font ASCII table offset */
	uint8_t _CurrentFontheight = 8;      /**<Holds current font height in bits */
};
