/*!
	@file SSD1306_OLED_font.hpp
	@brief   OLED driven by SSD1306 controller. font data file 12 fonts.
	@author Gavin Lyons.
	@note Fonts are 1-6 are Vertically addressed single dimension array
			Fonts 7-12 are Horizontally addressed 2 dimension array flipped 90 degrees.
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
		-#  Font_11 Mia
		-#  Font_12 Dedica

*/

#pragma once

#include <cstdint>


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
extern const uint8_t (* pFontMia8x16ptr)[16]; /**< Pointer to Mia font data */
extern const uint8_t (* pFontDedica8x12ptr)[12]; /**< Pointer to dedica font data */
