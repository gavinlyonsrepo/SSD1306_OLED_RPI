/*
* Project Name: SSD1306_OLED_RPI
* File: SSD1306_OLED_font.hpp
* Author: Gavin Lyons.
* URL: https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI
*/

#ifndef _SSD1306_OLED_font_H
#define _SSD1306_OLED_font_H

#include <stdint.h>


typedef enum 
{
	OLEDFontType_Default = 1,
	OLEDFontType_Thick = 2, // NO LOWERCASE
	OLEDFontType_SevenSeg = 3,
	OLEDFontType_Wide = 4, // NO LOWERCASE
	OLEDFontType_Tiny = 5,
	OLEDFontType_Homespun = 6,
	OLEDFontType_Bignum = 7, // NUMBERS + : . ,one size
	OLEDFontType_Mednum = 8   // NUMBERS + : . ,one size
}OLEDFontType_e;

typedef enum 
{
	OLEDFontWidth_3 = 3,
	OLEDFontWidth_5 = 5, 
	OLEDFontWidth_7 = 7, 
	OLEDFontWidth_4 = 4, 
	OLEDFontWidth_8 = 8,
	OLEDFontWidth_16 = 16
}OLEDFontWidth_e; // width of the font in bytes cols.

typedef enum 
{
	OLEDFontOffset_Extend = 0x00, //   extends ASCII
	OLEDFontOffset_Space = 0x20,  // Starts at Space
	OLEDFontOffset_Number = 0x30,  // Starts at number '0'
}OLEDFontOffset_e; // font offset in the ASCII table

typedef enum 
{
	OLEDFontHeight_8 = 8, 
	OLEDFontHeight_16 = 16, 
	OLEDFontHeight_32 = 32
}OLEDFontHeight_e; // height of the font in bits

// (1) default  (FUll ASCII with mods)
// (2) thick (NO LOWERCASE)
// (3) seven segment 
// (4) wide (NO LOWERCASE)
// (5) tiny
// (6) homespun 
// (7) big numbers (NUMBERS ONLY )
// (8) med numbers (NUMBERS ONLY )

extern const unsigned char * pFontDefaultptr;
extern const unsigned char * pFontThickptr;
extern const unsigned char * pFontSevenSegptr;
extern const unsigned char * pFontWideptr;
extern const  unsigned char * pFontTinyptr;
extern const unsigned char * pFontHomeSpunptr;
extern const uint8_t (* pFontBigNumptr)[64];
extern const uint8_t (* pFontMedNumptr)[32]; 

#endif 
