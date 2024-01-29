 /*!
	@file SSD1306_OLED_graphics.hpp
	@brief OLED driven by SSD1306 controller. header file
		for the graphics  based functions.
	@details Project Name: SSD1306_OLED_RPI
		URL: https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI
	@author  Gavin Lyons
*/

#pragma once

#include <cstdio>
#include <cstdint>
#include <cmath> // for "abs"
#include "SSD1306_OLED_Print.hpp"
#include "SSD1306_OLED_font.hpp"

#define swapOLEDRPI(a, b) { int16_t t = a; a = b; b = t; }


/*! Enum to define return codes from some text and bitmap functions  */
enum OLED_Return_Codes_e : uint8_t
{
	OLED_Success = 0,                /**< Success!*/
	OLED_WrongFont = 2,              /**< Wrong Font selected for this method, There are two families of font included with different overloaded functions*/
	OLED_CharScreenBounds = 3,       /**< Text Character is out of Screen bounds, Check x and y*/
	OLED_CharFontASCIIRange = 4,     /**< Text Character is outside of chosen Fonts ASCII range, Check the selected Fonts ASCII range.*/
	OLED_CharArrayNullptr = 5,       /**< Text Character Array is an invalid pointer object*/
	OLED_BitmapNullptr = 7,          /**< The Bitmap data array is an invalid pointer object*/
	OLED_BitmapScreenBounds = 8,     /**< The bitmap starting point is outside screen bounds check x and y*/
	OLED_BitmapLargerThanScreen = 9, /**< The Bitmap is larger than screen, check  w and h*/
	OLED_BitmapVerticalSize = 10,    /**< A vertical Bitmap's height must be divisible by 8. */
	OLED_BitmapHorizontalSize = 11,  /**< A horizontal Bitmap's width  must be divisible by 8  */
	OLED_BitmapSize = 12,            /**< Size of the Bitmap is incorrect: BitmapSize(vertical)!=(w*(h/8),BitmapSize(horizontal)!=(w/8)*h*/
	OLED_CustomCharLen = 13          /**< CustomChar array must always be 5 bytes long*/
};

/*! Enum to hold current screen rotation in degrees  */
enum OLED_rotate_e : uint8_t
{
	OLED_Degrees_0 =   0,    /**< OLED screen rotated 0 degrees */
	OLED_Degrees_90 =  1,    /**< OLED screen rotated 90 degrees  */
	OLED_Degrees_180 = 2,    /**< OLED screen rotated 180 degrees  */
	OLED_Degrees_270 = 3     /**< OLED screen rotated 270 degrees */
};

/*! Enum to define current font type selected  */
enum OLEDFontType_e : uint8_t
{
	OLEDFont_Default = 1,  /**<  (1) default  (FUll ASCII with mods) */
	OLEDFont_Thick = 2,    /**<  (2) thick (NO LOWERCASE) */
	OLEDFont_SevenSeg = 3, /**<  (3) seven segment  */
	OLEDFont_Wide = 4,     /**<  (4) wide (NO LOWERCASE) */
	OLEDFont_Tiny = 5,     /**<  (5) tiny */
	OLEDFont_Homespun = 6, /**<  (6) HomeSpun */
	OLEDFont_Bignum = 7,   /**< (7) big numbers  NUMBERS only + : . ,fixed size */
	OLEDFont_Mednum = 8,   /**< (8) Med numbers NUMBERS + : . , fixed size */
	OLEDFont_ArialRound = 9,   /**< Arial round */
	OLEDFont_ArialBold = 10,    /**< Arial bold */
	OLEDFont_Mia = 11,        /**< Mia font */
	OLEDFont_Dedica = 12       /**< dedica font */
};

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
	void setRotation(OLED_rotate_e m);
	OLED_rotate_e getRotation();
	int16_t height(void) const;
	int16_t width(void) const;
	
	// Text & font related member functions 
	virtual size_t write(uint8_t);
	OLED_Return_Codes_e drawChar(uint8_t x, uint8_t y, uint8_t c, uint8_t color ,uint8_t bg);
	OLED_Return_Codes_e drawText(uint8_t x, uint8_t y, char *pText, uint8_t color, uint8_t bg);
	OLED_Return_Codes_e drawText(uint8_t x, uint8_t y, char *pText, uint8_t color, uint8_t bg, uint8_t size);
	OLED_Return_Codes_e drawChar(int16_t x, int16_t y, unsigned char c, uint8_t color,
	  uint8_t bg, uint8_t size);
	void setTextColor(uint8_t c);
	void setTextColor(uint8_t c, uint8_t bg);
	void setTextSize(uint8_t s);
	void setTextWrap(bool w);
	void setFontNum(OLEDFontType_e FontNumber);

 protected:
	
	OLED_rotate_e  _OLED_rotate = OLED_Degrees_0; /**< Enum to hold rotation */
	const int16_t WIDTH;  /**< This is the 'raw' display w - never changes */
	const int16_t HEIGHT;  /**< This is the 'raw' display h - never changes*/
	int16_t _width;  /**< Display w as modified by current _rotation*/
	int16_t _height;  /**< Display h as modified by current _rotation*/
	int16_t _cursor_x; /**< Current X co-ord cursor position */
	int16_t _cursor_y;  /**< Current Y co-ord cursor position */
	
	uint8_t _textColor;  /**< Text foreground color */
	uint8_t _textBgColor;   /**< Text background color */
	uint8_t   _textSize = 1; /**< Size of text ,fonts 1-6 */
	bool _textwrap;          /**< If set, '_textwrap' text at right edge of display*/
	
private:

/*!  Width of the font in bits(pixels)  * (N bytes cols) */
enum OLEDFontWidth_e 
{
	OLEDFontWidth_3 = 3,  /**< 3 tiny font */
	OLEDFontWidth_4 = 4,  /**< 4 seven segment font */ 
	OLEDFontWidth_5 = 5,   /**< 5 default font */
	OLEDFontWidth_6 = 6,   /**< 12 dedica font  */
	OLEDFontWidth_7 = 7,  /**< 7 homespun & thick font*/
	OLEDFontWidth_8 = 8,  /**< 8 wide + mia font */
	OLEDFontWidth_16 = 16 /**< 16 font 7-10 */
};

/*! font offset in the ASCII table */
enum OLEDFontOffset_e : uint8_t
{
	OLEDFontOffset_Extend = 0x00,     /**<  Full ASCII */
	OLEDFontOffset_Space = 0x20,      /**< Starts at Space  */
	OLEDFontOffset_Minus = 0x2D,      /**< Starts at '-' */
	OLEDFontOffset_Number = 0x30   /**<  Starts at number '0' */
};

/*! height of the font in bits or pixels */
enum OLEDFontHeight_e : uint8_t
{
	OLEDFontHeight_8 = 8,    /**< 8 font  1-6 at size 1*/
	OLEDFontHeight_12 = 12, /**< 12 bit font 12 */
	OLEDFontHeight_16 = 16,  /**< 16 bit high font 8 & 10  */
	OLEDFontHeight_24 = 24, /**< 24 bit font 9 */
	OLEDFontHeight_32 = 32  /**<  32 bit font 7 */
}; 

/*! Number of ASCII characters in Font */
enum OLEDFontLength_e : uint8_t
{
	OLEDFontLenNumeric = 14,         /* Numeric + : - . forward slash 0x2D - 0x3A */
	OLEDFontLenAlphaNumNoLCase = 59, /* " " to "Z" 0x20-0x5A*/
	OLEDFontLenAlphaNum = 95,        /* " "  to "~" 0x20-0x7E */
	OLEDFontLenAll = 255            /**Full Range  0-0xFF */
};
	uint8_t _FontNumber = 1;                /**< Holds current font number */
	uint8_t _CurrentFontWidth = 5;        /**<Holds current font width in bits */
	uint8_t _CurrentFontoffset = 0x00;  /**<Holds current font ASCII table offset */
	uint8_t _CurrentFontheight = 8;      /**<Holds current font height in bits */
	uint8_t _CurrentFontLength = 255;/**<Holds current font number of characters */
};
