/*
* Project Name: SSD1306_OLED
* File:SSD1306_OLED_graphics.cpp
* Description: header file for the  graphics functions
* Author: Gavin Lyons.
* URL: https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI
*/

#include "SSD1306_OLED_graphics.h"
#include "SSD1306_OLED.h"


SSD1306_graphics::SSD1306_graphics(int16_t w, int16_t h):
	WIDTH(w), HEIGHT(h)
{
	_width    = WIDTH;
	_height   = HEIGHT;
	cursor_y  = cursor_x    = 0;
	rotation = 0;
	textsize  = 1;
	textcolor = textbgcolor = 0xFF;
	wrap      = true;
}

// Draw a circle outline
void SSD1306_graphics::drawCircle(int16_t x0, int16_t y0, int16_t r,
	uint8_t color) {
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	drawPixel(x0  , y0+r, color);
	drawPixel(x0  , y0-r, color);
	drawPixel(x0+r, y0  , color);
	drawPixel(x0-r, y0  , color);

	while (x<y) {
	if (f >= 0) {
		y--;
		ddF_y += 2;
		f += ddF_y;
	}
	x++;
	ddF_x += 2;
	f += ddF_x;
	
	drawPixel(x0 + x, y0 + y, color);
	drawPixel(x0 - x, y0 + y, color);
	drawPixel(x0 + x, y0 - y, color);
	drawPixel(x0 - x, y0 - y, color);
	drawPixel(x0 + y, y0 + x, color);
	drawPixel(x0 - y, y0 + x, color);
	drawPixel(x0 + y, y0 - x, color);
	drawPixel(x0 - y, y0 - x, color);
	}
}

void SSD1306_graphics::drawCircleHelper( int16_t x0, int16_t y0,
				 int16_t r, uint8_t cornername, uint8_t color) {
	int16_t f     = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x     = 0;
	int16_t y     = r;

	while (x<y) {
	if (f >= 0) {
		y--;
		ddF_y += 2;
		f     += ddF_y;
	}
	x++;
	ddF_x += 2;
	f     += ddF_x;
	if (cornername & 0x4) {
		drawPixel(x0 + x, y0 + y, color);
		drawPixel(x0 + y, y0 + x, color);
	} 
	if (cornername & 0x2) {
		drawPixel(x0 + x, y0 - y, color);
		drawPixel(x0 + y, y0 - x, color);
	}
	if (cornername & 0x8) {
		drawPixel(x0 - y, y0 + x, color);
		drawPixel(x0 - x, y0 + y, color);
	}
	if (cornername & 0x1) {
		drawPixel(x0 - y, y0 - x, color);
		drawPixel(x0 - x, y0 - y, color);
	}
	}
}

void SSD1306_graphics::fillCircle(int16_t x0, int16_t y0, int16_t r,
					uint8_t color) {
	drawFastVLine(x0, y0-r, 2*r+1, color);
	fillCircleHelper(x0, y0, r, 3, 0, color);
}

// Used to do circles and roundrects
void SSD1306_graphics::fillCircleHelper(int16_t x0, int16_t y0, int16_t r,
	uint8_t cornername, int16_t delta, uint8_t color) {

	int16_t f     = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x     = 0;
	int16_t y     = r;

	while (x<y) {
	if (f >= 0) {
		y--;
		ddF_y += 2;
		f     += ddF_y;
	}
	x++;
	ddF_x += 2;
	f     += ddF_x;

	if (cornername & 0x1) {
		drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
		drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
	}
	if (cornername & 0x2) {
		drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
		drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
	}
	}
}


void SSD1306_graphics::drawLine(int16_t x0, int16_t y0,
				int16_t x1, int16_t y1,
				uint8_t color) {
	int16_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
	swap(x0, y0);
	swap(x1, y1);
	}

	if (x0 > x1) {
	swap(x0, x1);
	swap(y0, y1);
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1) {
	ystep = 1;
	} else {
	ystep = -1;
	}

	for (; x0<=x1; x0++) {
	if (steep) {
		drawPixel(y0, x0, color);
	} else {
		drawPixel(x0, y0, color);
	}
	err -= dy;
	if (err < 0) {
		y0 += ystep;
		err += dx;
	}
	}
}

// Draw a rectangle
void SSD1306_graphics::drawRect(int16_t x, int16_t y,
				int16_t w, int16_t h,
				uint8_t color) {
	drawFastHLine(x, y, w, color);
	drawFastHLine(x, y+h-1, w, color);
	drawFastVLine(x, y, h, color);
	drawFastVLine(x+w-1, y, h, color);
}

void SSD1306_graphics::drawFastVLine(int16_t x, int16_t y,
				 int16_t h, uint8_t color) {
	drawLine(x, y, x, y+h-1, color);
}

void SSD1306_graphics::drawFastHLine(int16_t x, int16_t y,
				 int16_t w, uint8_t color) {
		drawLine(x, y, x+w-1, y, color);
}

void SSD1306_graphics::fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
				uint8_t color) {
	for (int16_t i=x; i<x+w; i++) {
	drawFastVLine(i, y, h, color);
	}
}

void SSD1306_graphics::fillScreen(uint8_t color) {
	fillRect(0, 0, _width, _height, color);
}

// Draw a rounded rectangle
void SSD1306_graphics::drawRoundRect(int16_t x, int16_t y, int16_t w,
	int16_t h, int16_t r, uint8_t color) {
	drawFastHLine(x+r  , y    , w-2*r, color); // Top
	drawFastHLine(x+r  , y+h-1, w-2*r, color); // Bottom
	drawFastVLine(x    , y+r  , h-2*r, color); // Left
	drawFastVLine(x+w-1, y+r  , h-2*r, color); // Right
	// draw four corners
	drawCircleHelper(x+r    , y+r    , r, 1, color);
	drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
	drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
	drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}

// Fill a rounded rectangle
void SSD1306_graphics::fillRoundRect(int16_t x, int16_t y, int16_t w,
				 int16_t h, int16_t r, uint8_t color) {
	// smarter version
	fillRect(x+r, y, w-2*r, h, color);

	// draw four corners
	fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
	fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}

// Draw a triangle
void SSD1306_graphics::drawTriangle(int16_t x0, int16_t y0,
				int16_t x1, int16_t y1,
				int16_t x2, int16_t y2, uint8_t color) {
	drawLine(x0, y0, x1, y1, color);
	drawLine(x1, y1, x2, y2, color);
	drawLine(x2, y2, x0, y0, color);
}

// Fill a triangle
void SSD1306_graphics::fillTriangle ( int16_t x0, int16_t y0,
					int16_t x1, int16_t y1,
					int16_t x2, int16_t y2, uint8_t color) {

	int16_t a, b, y, last;

	// Sort coordinates by Y order (y2 >= y1 >= y0)
	if (y0 > y1) {
	swap(y0, y1); swap(x0, x1);
	}
	if (y1 > y2) {
	swap(y2, y1); swap(x2, x1);
	}
	if (y0 > y1) {
	swap(y0, y1); swap(x0, x1);
	}

	if(y0 == y2) { 
	a = b = x0;
	if(x1 < a)      a = x1;
	else if(x1 > b) b = x1;
	if(x2 < a)      a = x2;
	else if(x2 > b) b = x2;
	drawFastHLine(a, y0, b-a+1, color);
	return;
	}

	int16_t
	dx01 = x1 - x0,
	dy01 = y1 - y0,
	dx02 = x2 - x0,
	dy02 = y2 - y0,
	dx12 = x2 - x1,
	dy12 = y2 - y1;
	int32_t
	sa   = 0,
	sb   = 0;

	if(y1 == y2) last = y1;   // Include y1 scanline
	else         last = y1-1; // Skip it

	for(y=y0; y<=last; y++) {
	a   = x0 + sa / dy01;
	b   = x0 + sb / dy02;
	sa += dx01;
	sb += dx02;

	if(a > b) swap(a,b);
	drawFastHLine(a, y, b-a+1, color);
	}


	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for(; y<=y2; y++) {
	a   = x1 + sa / dy12;
	b   = x0 + sb / dy02;
	sa += dx12;
	sb += dx02;
	if(a > b) swap(a,b);
	drawFastHLine(a, y, b-a+1, color);
	}
}

// Desc called form the print class by print functions
// to draw most data types using polymorphism
size_t SSD1306_graphics::write(uint8_t character) 
{
	if (_FontNumber < OLEDFontType_Bignum)
	{
		if (character == '\n') {
		cursor_y += textsize*_CurrentFontheight;
		cursor_x  = 0;
		} else if (character== '\r') {
		// skip 
		} else {
		drawChar(cursor_x, cursor_y, character, textcolor, textbgcolor, textsize);
		cursor_x += textsize*(_CurrentFontWidth+1);
			if (wrap && (cursor_x > (_width - textsize*(_CurrentFontWidth+1)))) {
			  cursor_y += textsize*_CurrentFontheight;
			  cursor_x = 0;
			}
		}
	}else if (_FontNumber == OLEDFontType_Bignum || _FontNumber == OLEDFontType_Mednum)
	{
		uint8_t radius = 3;
		uint8_t SkipSpace = 0;
		if (_FontNumber == OLEDFontType_Mednum) radius = 2;
		
		switch (character)
		{
			case '\n': 
				cursor_y += _CurrentFontheight;
				cursor_x  = 0;
			break;
			case '\r': break;
			case '.':  // draw a circle for decimal & point skip a space.
				fillCircle(cursor_x+(_CurrentFontWidth/2), cursor_y + (_CurrentFontheight-6), decPointRadius, textcolor);
				SkipSpace = 1;
			break;
			case '-':  // draw a rect for negative number line and skip a space
				fillRect(cursor_x+2, cursor_y + (_CurrentFontheight/2)-2 ,_CurrentFontWidth-4 , decPointRadius+1,  textcolor);              
				SkipSpace = 1;
			break;
			default:
				drawCharNumFont(cursor_x, cursor_y, character, textcolor, textbgcolor);
				SkipSpace = 1;
			break;
		} // end of switch
		if (SkipSpace == 1)
		{
			cursor_x += (_CurrentFontWidth+1);
			if (wrap && (cursor_x  > (_width - (_CurrentFontWidth+1)))) 
			{
				cursor_y += _CurrentFontheight;
				cursor_x = 0;
			}
		}

	}
  return 1;
}

// Desc: writes a char (c) on the OLED
// Param 1 , 2 : coordinates (x, y).
// Param 3: The ASCII character
// Param 4: color 
// Param 5: background color
// Param 6: size 1  to  max
// Note Font 1-6 only
void SSD1306_graphics::drawChar(int16_t x, int16_t y, unsigned char c,
				uint8_t color, uint8_t bg, uint8_t size) {

	if((x >= _width)            || // Clip right
	 (y >= _height)           || // Clip bottom
	 ((x + (_CurrentFontWidth+1) * size - 1) < 0) || // Clip left
	 ((y + _CurrentFontheight * size - 1) < 0))   // Clip top
	return;

	for (int8_t i=0; i<(_CurrentFontWidth+1); i++ ) {
	uint8_t line;
	if (i == _CurrentFontWidth)
	{ 
		line = 0x0;
	}
	else 
	{
		switch (_FontNumber) 
		{
			case OLEDFontType_Default : line = pFontDefaultptr[((c - _CurrentFontoffset) * _CurrentFontWidth) + i]; break;
			case OLEDFontType_Thick : line = pFontThickptr[((c - _CurrentFontoffset) * _CurrentFontWidth) + i]; break;
			case OLEDFontType_SevenSeg: line = pFontSevenSegptr[((c - _CurrentFontoffset) * _CurrentFontWidth) + i]; break;
			case OLEDFontType_Wide : line = pFontWideptr[((c - _CurrentFontoffset) * _CurrentFontWidth) + i]; break;
			case OLEDFontType_Tiny : line = pFontTinyptr[((c - _CurrentFontoffset) * _CurrentFontWidth) + i]; break;
			case OLEDFontType_Homespun : line = pFontHomeSpunptr[((c - _CurrentFontoffset) * _CurrentFontWidth) + i]; break;
		default:
			printf("Error: Wrong font number ,must be 1-6\n");
			return;
		break;
		} //switch font linenumber
	}

	for (int8_t j = 0; j<_CurrentFontheight ; j++) 
	{
		if (line & 0x1) 
		{
		if (size == 1) // default size
			drawPixel(x+i, y+j, color);
		else  // big size
			fillRect(x+(i*size), y+(j*size), size, size, color);
		} else if (bg != color) 
		{
		if (size == 1) // default size
			drawPixel(x+i, y+j, bg);
		else {  // big size
			fillRect(x+i*size, y+j*size, size, size, bg);
		}
		}
		line >>= 1;
	}
	}
}

void SSD1306_graphics::setCursor(int16_t x, int16_t y) {
	cursor_x = x;
	cursor_y = y;
}

void SSD1306_graphics::setTextSize(uint8_t s) {
	textsize = (s > 0) ? s : 1;
}

void SSD1306_graphics::setTextColor(uint8_t c) {
	textcolor = textbgcolor = c;
}

void SSD1306_graphics::setTextColor(uint8_t c, uint8_t b) {
	textcolor   = c;
	textbgcolor = b; 
}

void SSD1306_graphics::setTextWrap(bool w) {
	wrap = w;
}

int16_t SSD1306_graphics::width(void) const {
	return _width;
}
 
int16_t SSD1306_graphics::height(void) const {
	return _height;
}

uint8_t SSD1306_graphics::getRotation(void) const {
	return rotation;
}

void SSD1306_graphics::setRotation(uint8_t x) {
	rotation = (x & 3);
	switch(rotation) {
	 case 0:
	 case 2:
		_width  = WIDTH;
		_height = HEIGHT;
		break;
	 case 1:
	 case 3:
		_width  = HEIGHT;
		_height = WIDTH;
		break;
	}
}


// Desc :  Set the font number
// Param1: OLEDFontType_e  enum , fontnumber 1-8 
// 1=default 2=thick 3=seven segment 4=wide 5=tiny 6=homespun
// 7= bignum 8=mednum

void SSD1306_graphics::setFontNum(OLEDFontType_e FontNumber) 
{
	_FontNumber = FontNumber;

	switch (_FontNumber) {
	case OLEDFontType_Default:  // Norm default 5 by 8
		_CurrentFontWidth = OLEDFontWidth_5;
		_CurrentFontoffset =  OLEDFontOffset_Extend;
		_CurrentFontheight = OLEDFontHeight_8;
	break; 
	case OLEDFontType_Thick: // Thick 7 by 8 (NO LOWERCASE LETTERS)
		_CurrentFontWidth = OLEDFontWidth_7;
		_CurrentFontoffset = OLEDFontOffset_Space;
		_CurrentFontheight = OLEDFontHeight_8;
	break; 
	case OLEDFontType_SevenSeg:  // Seven segment 4 by 8
		_CurrentFontWidth = OLEDFontWidth_4;
		_CurrentFontoffset = OLEDFontOffset_Space;
		_CurrentFontheight = OLEDFontHeight_8;
	break;
	case OLEDFontType_Wide : // Wide  8 by 8 (NO LOWERCASE LETTERS)
		_CurrentFontWidth = OLEDFontWidth_8;
		_CurrentFontoffset = OLEDFontOffset_Space;
		_CurrentFontheight = OLEDFontHeight_8;
	break; 
	case OLEDFontType_Tiny:  // tiny 3 by 8
		_CurrentFontWidth = OLEDFontWidth_3;
		_CurrentFontoffset =  OLEDFontOffset_Space;
		_CurrentFontheight = OLEDFontHeight_8;
	break;
	case OLEDFontType_Homespun: // homespun 7 by 8 
		_CurrentFontWidth = OLEDFontWidth_7;
		_CurrentFontoffset = OLEDFontOffset_Space;
		_CurrentFontheight = OLEDFontHeight_8;
	break;
	case OLEDFontType_Bignum : // big nums 16 by 32 (NUMBERS + : only)
		_CurrentFontWidth = OLEDFontWidth_16;
		_CurrentFontoffset = OLEDFontOffset_Number;
		_CurrentFontheight = OLEDFontHeight_32;
	break; 
	case OLEDFontType_Mednum: // med nums 16 by 16 (NUMBERS + : only)
		_CurrentFontWidth = OLEDFontWidth_16;
		_CurrentFontoffset =  OLEDFontOffset_Number;
		_CurrentFontheight = OLEDFontHeight_16;
	break;
	default: // if wrong font num passed in,  set to default
		_CurrentFontWidth = OLEDFontWidth_5;
		_CurrentFontoffset =  OLEDFontOffset_Extend;
		_CurrentFontheight = OLEDFontHeight_8;
		_FontNumber = OLEDFontType_Default;
	break;
    }
}

// Desc: writes a char (c) on the OLED
// Param 1 , 2 : coordinates (x, y).
// Param 3: The ASCII character
// Param 4: color 
// Param 5: background color
// Notes for font 7 , 8 only

void SSD1306_graphics::drawCharNumFont(uint8_t x, uint8_t y, uint8_t c, uint8_t color , uint8_t bg) 
{
	if (_FontNumber < OLEDFontType_Bignum)
	{
		printf("Error: Wrong font selected, must be 7 or 8 \n");
		return;
	}
	
	uint8_t i, j;
	uint8_t ctemp = 0, y0 = y; 

	for (i = 0; i < _CurrentFontheight*2; i++) 
	{
		if (_FontNumber == OLEDFontType_Bignum){
			ctemp = pFontBigNumptr[c - _CurrentFontoffset][i];
		}
		else if (_FontNumber == OLEDFontType_Mednum){
			ctemp = pFontMedNumptr[c - _CurrentFontoffset][i];
		}
		
		for (j = 0; j < 8; j++) 
		{
			if (ctemp & 0x80) 
			{
				drawPixel(x, y, color);
			} else 
			{
				drawPixel(x, y, bg);
			}

			ctemp <<= 1;
			y++;
			if ((y - y0) == _CurrentFontheight) 
			{
				y = y0;
				x++;
				break;
			}
		}
	}
}

// Desc: Writes text string (*ptext) on the OLED
// Param 1 , 2 : coordinates (x, y).
// Param 3: pointer to string 
// Param 4: color 
// Param 5: background color
// Notes for font 7-8 only 

void SSD1306_graphics::drawTextNumFont(uint8_t x, uint8_t y, 
						char *pText, uint8_t color, uint8_t bg) 
{
	if (_FontNumber < OLEDFontType_Bignum)
	{
		printf("Error: Wrong font selected, must be 7 or 8 \n");
		return;
	}
	while (*pText != '\0') 
	{
		if (x > (_width - _CurrentFontWidth )) 
		{
			x = 0;
			y += _CurrentFontheight;
			if (y > (_height - _CurrentFontheight )) 
			{
				y = x = 0;
			}
		}
		drawCharNumFont(x, y, *pText, color, bg);
		x += _CurrentFontWidth ;
		pText++;
	}
}

// Desc: Writes text string (*ptext) on the OLED
// Param 1 , 2 : coordinates (x, y).
// Param 3: pointer to string 
// Param 4: color 
// Param 5: background color
// Notes for font 1- 6 only
void SSD1306_graphics::drawText(uint8_t x, uint8_t y, char *pText, uint8_t color, uint8_t bg, uint8_t size) 
{
	if (_FontNumber >= OLEDFontType_Bignum)
	{
		printf("Error: Wrong font selected, must be 1-6 \n");
		return;
	}
	uint8_t cursor_x, cursor_y;
	cursor_x = x, cursor_y = y;
	  while (*pText != '\0') 
	  {
		if (wrap && ((cursor_x + size * _CurrentFontWidth) > _width)) 
		{
			cursor_x = 0;
			cursor_y = cursor_y + size * 7 + 3;
			if (cursor_y > _height) cursor_y = _height;
		}
		drawChar(cursor_x, cursor_y, *pText, color, bg, size);
		cursor_x = cursor_x + size * (_CurrentFontWidth + 1);
		if (cursor_x > _width) cursor_x = _width;
		pText++;
	  }
}
