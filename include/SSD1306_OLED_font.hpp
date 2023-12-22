/*!
	@file SSD1306_OLED_font.hpp
	@brief   OLED driven by SSD1306 controller. font data file 10 fonts.
	@author Gavin Lyons.
	@note Fonts are 1-6 are Vertically addressed single dimension array
			Fonts 7-10 are Horizontally addressed 2 dimension array flipped 90 degrees.
	@details 
		-#  Font_One  default  (FUll ASCII with mods)
		-#  Font_Two  thick (NO LOWERCASE)
		-#  Font_Three seven segment 
		-#  Font_Four wide (NO LOWERCASE)
		-#  Font_Five  tiny
		-#  Font_Six HomeSpun
		-#  Font_Seven big numbers (NUMBERS ONLY + : . ,one size )
		-#  Font_Eight Medium numbers (NUMBERS ONLY + : . ,one size)
		-#  Font_Nine Arial Round
		-#  Font_Ten Arial Bold

*/

#pragma once

#include <stdint.h>

/*! Enum to define current font type selected  */
enum OLEDFontType_e : uint8_t
{
	OLEDFontType_Default = 1,  /**<  (1) default  (FUll ASCII with mods) */
	OLEDFontType_Thick = 2,    /**<  (2) thick (NO LOWERCASE) */
	OLEDFontType_SevenSeg = 3, /**<  (3) seven segment  */
	OLEDFontType_Wide = 4,     /**<  (4) wide (NO LOWERCASE) */
	OLEDFontType_Tiny = 5,     /**<  (5) tiny */
	OLEDFontType_Homespun = 6, /**<  (6) HomeSpun */
	OLEDFontType_Bignum = 7,   /**< (7) big numbers  NUMBERS only + : . ,fixed size */
	OLEDFontType_Mednum = 8,   /**< (8) Med numbers NUMBERS + : . , fixed size */
	OLEDFontType_ArialRound = 9,   /**< Arial round */
	OLEDFontType_ArialBold = 10    /**< Arial bold */
};

/*!  Width of the font in bits(pixels)  * (N bytes cols) */
enum OLEDFontWidth_e 
{
	OLEDFontWidth_3 = 3,  /**< 3 tiny font */
	OLEDFontWidth_4 = 4,  /**< 4 seven segment font */ 
	OLEDFontWidth_5 = 5,   /**< 5 default font */
	OLEDFontWidth_7 = 7,  /**< 7 homespun & thick font*/
	OLEDFontWidth_8 = 8,  /**< 8 wide font */
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
	OLEDFontHeight_8 = 8,      /**< 8 font  1-6 at size 1*/
	OLEDFontHeight_16 = 16,  /**< 16 bit high font 8 & 10  */
	OLEDFontHeight_24 = 24, /**< 24 bit font 9 */
	OLEDFontHeight_32 = 32  /**<  32 bit font 7 */
}; 



// Font data is in the cpp file accessed thru extern pointers.

extern const unsigned char * pFontDefaultptr; /**< Pointer to default font data  */
extern const unsigned char * pFontThickptr; /**< Pointer to thick font data  */
extern const unsigned char * pFontSevenSegptr; /**< Pointer to seven segment font data  */
extern const unsigned char * pFontWideptr; /**< Pointer to wide font data  */
extern const unsigned char * pFontTinyptr; /**< Pointer to tiny font data  */
extern const unsigned char * pFontHomeSpunptr; /**< Pointer to homespun font data  */
extern const uint8_t (* pFontBigNumptr)[64]; /**< Pointer to big numbers font data  */
extern const uint8_t (* pFontMedNumptr)[32]; /**< Pointer to medium numbers font data  */
extern const uint8_t (* pFontArial16x24ptr)[48]; /**< Pointer to Arial Round font data */
extern const uint8_t (* pFontArial16x16ptr)[32]; /**< Pointer to Arial bold font data */

