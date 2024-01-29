/*!
* @file SSD1306_OLED_graphics.cpp
* @brief  OLED driven by SSD1306 controller. Header file for the graphics functions
* @author Gavin Lyons.
* @details https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI
*/

#include "SSD1306_OLED_graphics.hpp"

/*!
	@brief init the OLED  Graphics class object
	@param w width defined  in sub-class
	@param h height defined in sub-class
 */
SSD1306_graphics::SSD1306_graphics(int16_t w, int16_t h):
	WIDTH(w), HEIGHT(h)
{
	_width     = WIDTH;
	_height    = HEIGHT;
	_cursor_y  = 0;
	_cursor_x  = 0;
	_textSize  = 1;
	_textColor = 0x00;
	_textBgColor = 0xFF;
	_textwrap  = true;
}

/*!
	@brief draws a circle where (x0,y0) are center coordinates an r is circle radius.
	@param x0 circle center x position
	@param y0 circle center y position
	@param r radius of circle
	@param color The color of the circle
*/
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

/*!
	@brief Used internally by drawRoundRect
*/
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

/*!
	@brief fills a circle where (x0,y0) are center coordinates an r is circle radius.
	@param x0 circle center x position
	@param y0 circle center y position
	@param r radius of circle
	@param color color of the filled circle 
*/
void SSD1306_graphics::fillCircle(int16_t x0, int16_t y0, int16_t r,
					uint8_t color) {
	drawFastVLine(x0, y0-r, 2*r+1, color);
	fillCircleHelper(x0, y0, r, 3, 0, color);
}

/*!
	@brief Used internally by fill circle fillRoundRect and fillcircle
*/
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

/*!
	@brief draws a line from (x0,y0) to (x1,y1).
	@param x0 x start coordinate
	@param y0 y start coordinate
	@param x1 x end coordinate
	@param y1 y end coordinate
	@param color color to draw line
*/
void SSD1306_graphics::drawLine(int16_t x0, int16_t y0,
				int16_t x1, int16_t y1,
				uint8_t color) {
	int16_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
	swapOLEDRPI(x0, y0);
	swapOLEDRPI(x1, y1);
	}

	if (x0 > x1) {
	swapOLEDRPI(x0, x1);
	swapOLEDRPI(y0, y1);
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

/*!
	@brief draws rectangle at (x,y) where h is height and w is width of the rectangle.
	@param x x start coordinate
	@param y y start coordinate
	@param w width of the rectangle
	@param h height of the rectangle
	@param color color to draw  rect
*/
void SSD1306_graphics::drawRect(int16_t x, int16_t y,
				int16_t w, int16_t h,
				uint8_t color) {
	drawFastHLine(x, y, w, color);
	drawFastHLine(x, y+h-1, w, color);
	drawFastVLine(x, y, h, color);
	drawFastVLine(x+w-1, y, h, color);
}


/*!
	@brief Draws a vertical line starting at (x,y) with height h.
	@param x The starting x coordinate
	@param y The starting y coordinate
	@param h The height of the line
	@param color The color of the line
*/
void SSD1306_graphics::drawFastVLine(int16_t x, int16_t y,
				 int16_t h, uint8_t color) {
	drawLine(x, y, x, y+h-1, color);
}

/*!
	@brief Draws a horizontal line starting at (x,y) with width w.
	@param x The starting x coordinate
	@param y The starting y coordinate
	@param w The width of the line
	@param color The color of the line 
*/
void SSD1306_graphics::drawFastHLine(int16_t x, int16_t y,
				 int16_t w, uint8_t color) {
		drawLine(x, y, x+w-1, y, color);
}

/*!
	@brief fills a rectangle starting from coordinates (x,y) with width of w and height of h.
	@param x x coordinate
	@param y y coordinate
	@param w width of the rectangle
	@param h height of the rectangle
	@param color color to fill  rectangle 
*/
void SSD1306_graphics::fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
				uint8_t color) {
	for (int16_t i=x; i<x+w; i++) {
	drawFastVLine(i, y, h, color);
	}
}

/*!
	@brief Fills the whole screen with a given color.
	@param  color color to fill screen
*/
void SSD1306_graphics::fillScreen(uint8_t color) {
	fillRect(0, 0, _width, _height, color);
}

/*!
	@brief draws a rectangle with rounded edges
	@param x x start coordinate
	@param y y start coordinate
	@param w width of the rectangle
	@param h height of the rectangle
	@param r radius of the rounded edges
	@param color color to draw rounded rectangle 
*/
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

/*!
	@brief Fills a rectangle with rounded edges
	@param x x start coordinate
	@param y y start coordinate
	@param w width of the rectangle
	@param h height of the rectangle
	@param r  radius of the rounded edges
	@param color color to fill round  rectangle 
*/
void SSD1306_graphics::fillRoundRect(int16_t x, int16_t y, int16_t w,
				 int16_t h, int16_t r, uint8_t color) {
	// smarter version
	fillRect(x+r, y, w-2*r, h, color);

	// draw four corners
	fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
	fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}

/*!
	@brief draws a triangle of coordinates (x0,y0), (x1,y1) and (x2,y2).
	@param x0 x start coordinate point 1
	@param y0 y start coordinate point 1
	@param x1 x start coordinate point 2
	@param y1 y start coordinate point 2
	@param x2 x start coordinate point 3
	@param y2 y start coordinate point 3
	@param color color to draw triangle 
*/
void SSD1306_graphics::drawTriangle(int16_t x0, int16_t y0,
				int16_t x1, int16_t y1,
				int16_t x2, int16_t y2, uint8_t color) {
	drawLine(x0, y0, x1, y1, color);
	drawLine(x1, y1, x2, y2, color);
	drawLine(x2, y2, x0, y0, color);
}

/*!
	@brief Fills a triangle of coordinates (x0,y0), (x1,y1) and (x2,y2).
	@param x0 x start coordinate point 1
	@param y0 y start coordinate point 1
	@param x1 x start coordinate point 2
	@param y1 y start coordinate point 2
	@param x2 x start coordinate point 3
	@param y2 y start coordinate point 3
	@param color color to fill  triangle
*/
void SSD1306_graphics::fillTriangle ( int16_t x0, int16_t y0,
					int16_t x1, int16_t y1,
					int16_t x2, int16_t y2, uint8_t color) {

	int16_t a, b, y, last;

	if (y0 > y1) {
	swapOLEDRPI(y0, y1); swapOLEDRPI(x0, x1);
	}
	if (y1 > y2) {
	swapOLEDRPI(y2, y1); swapOLEDRPI(x2, x1);
	}
	if (y0 > y1) {
	swapOLEDRPI(y0, y1); swapOLEDRPI(x0, x1);
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

	if(y1 == y2) last = y1;   
	else         last = y1-1; 

	for(y=y0; y<=last; y++) {
	a   = x0 + sa / dy01;
	b   = x0 + sb / dy02;
	sa += dx01;
	sb += dx02;

	if(a > b) swapOLEDRPI(a,b);
	drawFastHLine(a, y, b-a+1, color);
	}


	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for(; y<=y2; y++) {
	a   = x1 + sa / dy12;
	b   = x0 + sb / dy02;
	sa += dx12;
	sb += dx02;
	if(a > b) swapOLEDRPI(a,b);
	drawFastHLine(a, y, b-a+1, color);
	}
}

/*!
	@brief called by the print class after it converts the data to a character
	@param character 
	@note draw most data types using polymorphism
*/
size_t SSD1306_graphics::write(uint8_t character) 
{
	int DrawCharReturnCode;
	if (_FontNumber < OLEDFont_Bignum)
	{
		switch (character)
		{
		case '\n':
			_cursor_y += _textSize*_CurrentFontheight;
			_cursor_x  = 0;
		break;
		case'\r':/* skip */ break;
		default:
			DrawCharReturnCode = drawChar(_cursor_x, _cursor_y, character, _textColor, _textBgColor, _textSize) ;
			if(DrawCharReturnCode  != OLED_Success)
			{
				printf( "Error write_print method 1: Method drawChar failed:  %i\n",DrawCharReturnCode);
				return DrawCharReturnCode;
			}
			_cursor_x += _textSize*(_CurrentFontWidth+1);
			if (_textwrap && (_cursor_x > (_width - _textSize*(_CurrentFontWidth+1)))) 
			{
				_cursor_y += _textSize*_CurrentFontheight;
				_cursor_x = 0;
			}
		break;
		}
	}else // for font numbers 7-12
	{
		switch (character)
		{
			case '\n': 
				_cursor_y += _CurrentFontheight;
				_cursor_x  = 0;
			break;
			case '\r': /* skip */  break;
			default:
				DrawCharReturnCode = drawChar(_cursor_x, _cursor_y, character, _textColor, _textBgColor) ;
				if(DrawCharReturnCode  != OLED_Success)
				{
					printf( "Error write_print method 2 : Method drawChar failed: %i\n",DrawCharReturnCode);
					return DrawCharReturnCode;
				}
				_cursor_x += (_CurrentFontWidth);
				if (_textwrap && (_cursor_x  > (_width - (_CurrentFontWidth+1)))) 
				{
					_cursor_y += _CurrentFontheight;
					_cursor_x = 0;
				}
			break;
		} // end of switch
	} // end of else
  return 1;
}

/*!
	@brief  writes a character on the OLED
	@param  x X coordinate
	@param  y Y coordinate
	@param  character The ASCII character
	@param color  color
	@param bg background color
	@param size 1-x
	@return OLED_Return_Codes_e enum
	@note for font #1-6 only
*/
OLED_Return_Codes_e SSD1306_graphics::drawChar(int16_t x, int16_t y, unsigned char character,
				uint8_t color, uint8_t bg, uint8_t size) {

	// 1. Check for wrong font
	if (_FontNumber >= OLEDFont_Bignum)
	{
		printf("Error drawChar 1: Wrong font selected, must be font 1-6: %u \r\n",OLED_WrongFont);
		return OLED_WrongFont;
	}
	// 2. Check for screen out of  bounds
	if((x >= _width)            || // Clip right
	(y >= _height)           || // Clip bottom
	((x + (_CurrentFontWidth+1) * size - 1) < 0) || // Clip left
	((y + _CurrentFontheight  * size - 1) < 0))   // Clip top
	{
		printf("Error drawChar 2: Co-ordinates out of bounds : %u \r\n",OLED_CharScreenBounds );
		return OLED_CharScreenBounds;
	}
	// 3. Check for character out of font range bounds
	if ( character < _CurrentFontoffset || character >= (_CurrentFontLength+ _CurrentFontoffset))
	{
		printf("Error drawChar 3: Character out of Font bounds: %u:  %u  %u<->%u \r\n", OLED_CharFontASCIIRange, character,_CurrentFontoffset, (_CurrentFontLength + _CurrentFontoffset));
		return OLED_CharFontASCIIRange;
	}

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
			case OLEDFont_Default : line = pFontDefaultptr[((character - _CurrentFontoffset) * _CurrentFontWidth) + i]; break;
			case OLEDFont_Thick : line = pFontThickptr[((character - _CurrentFontoffset) * _CurrentFontWidth) + i]; break;
			case OLEDFont_SevenSeg: line = pFontSevenSegptr[((character - _CurrentFontoffset) * _CurrentFontWidth) + i]; break;
			case OLEDFont_Wide : line = pFontWideptr[((character - _CurrentFontoffset) * _CurrentFontWidth) + i]; break;
			case OLEDFont_Tiny : line = pFontTinyptr[((character - _CurrentFontoffset) * _CurrentFontWidth) + i]; break;
			case OLEDFont_Homespun : line = pFontHomeSpunptr[((character - _CurrentFontoffset) * _CurrentFontWidth) + i]; break;
		default:
			printf("Error drawChar 1: Wrong font selected, must be font 1-6 : %u\r\n", OLED_WrongFont);
			return OLED_WrongFont;
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
	return OLED_Success;
}

/*! 
	@brief set the cursor position  
	@param x X co-ord position 
	@param y Y co-ord position
*/
void SSD1306_graphics::setCursor(int16_t x, int16_t y) {
	_cursor_x = x;
	_cursor_y = y;
}

/*! 
	@brief set the text size , starts at 1 
	@param s Size of text 1-X 
*/
void SSD1306_graphics::setTextSize(uint8_t s) {_textSize = (s > 0) ? s : 1;}

/*! 
	@brief set the text color  
	@param c Color of text 
*/
void SSD1306_graphics::setTextColor(uint8_t c) {_textColor = _textBgColor = c;}

/*! 
	@brief set the text color  
	@param c Color of text foreground
	@param b color of background of text 
*/
void SSD1306_graphics::setTextColor(uint8_t c, uint8_t b) {
	_textColor   = c;
	_textBgColor = b; 
}

/*!
	@brief turn on or off screen _textwrap of the text (fonts 1-6)
	@param w TRUE on
*/
void SSD1306_graphics::setTextWrap(bool w) {_textwrap = w;}

/*!
	@brief Gets the width of the display (per current _rotation)
	@return width member of display in pixels 
*/
int16_t SSD1306_graphics::width(void) const {return _width;}
 
/*!
	@brief Gets the height of the display (per current _rotation)
	@return height member of display in pixels 
*/
int16_t SSD1306_graphics::height(void) const {return _height;}

 /*!
	@brief Gets the _rotation of the display 
	@return _rotation value 0-3
*/
OLED_rotate_e SSD1306_graphics::getRotation(void){return _OLED_rotate;}

 /*!
	@brief Sets the _rotation of the display 
	@param CurrentRotation value 0-3
*/
void SSD1306_graphics::setRotation(OLED_rotate_e CurrentRotation) {

	_OLED_rotate = CurrentRotation;
	switch(CurrentRotation) 
	{
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


/*!
	@brief   Set the current font type
	@param FontNumber enum OLEDFontType_e
*/
void SSD1306_graphics::setFontNum(OLEDFontType_e FontNumber) 
{
	_FontNumber = FontNumber;

	switch (_FontNumber) {
		case OLEDFont_Default:  // Norm default 5 by 8
			_CurrentFontWidth = OLEDFontWidth_5;
			_CurrentFontoffset =  OLEDFontOffset_Extend;
			_CurrentFontheight = OLEDFontHeight_8;
			_CurrentFontLength = OLEDFontLenAll;
		break;
		case OLEDFont_Thick: // Thick 7 by 8 (NO LOWERCASE LETTERS)
			_CurrentFontWidth = OLEDFontWidth_7;
			_CurrentFontoffset = OLEDFontOffset_Space;
			_CurrentFontheight = OLEDFontHeight_8;
			_CurrentFontLength = OLEDFontLenAlphaNumNoLCase;
		break;
		case OLEDFont_SevenSeg:  // Seven segment 4 by 8
			_CurrentFontWidth = OLEDFontWidth_4;
			_CurrentFontoffset = OLEDFontOffset_Space;
			_CurrentFontheight = OLEDFontHeight_8;
			_CurrentFontLength = OLEDFontLenAlphaNum;
		break;
		case OLEDFont_Wide : // Wide  8 by 8 (NO LOWERCASE LETTERS)
			_CurrentFontWidth = OLEDFontWidth_8;
			_CurrentFontoffset = OLEDFontOffset_Space;
			_CurrentFontheight = OLEDFontHeight_8;
			_CurrentFontLength = OLEDFontLenAlphaNumNoLCase;
		break;
		case OLEDFont_Tiny:  // tiny 3 by 8
			_CurrentFontWidth = OLEDFontWidth_3;
			_CurrentFontoffset =  OLEDFontOffset_Space;
			_CurrentFontheight = OLEDFontHeight_8;
			_CurrentFontLength = OLEDFontLenAlphaNum;
		break;
		case OLEDFont_Homespun: // homespun 7 by 8
			_CurrentFontWidth = OLEDFontWidth_7;
			_CurrentFontoffset = OLEDFontOffset_Space;
			_CurrentFontheight = OLEDFontHeight_8;
			_CurrentFontLength = OLEDFontLenAlphaNum;
		break;
		case OLEDFont_Bignum : // big nums 16 by 32 (NUMBERS)
			_CurrentFontWidth = OLEDFontWidth_16;
			_CurrentFontoffset = OLEDFontOffset_Minus;
			_CurrentFontheight = OLEDFontHeight_32;
			_CurrentFontLength = OLEDFontLenNumeric;
		break;
		case OLEDFont_Mednum: // med nums 16 by 16 (NUMBERS)
			_CurrentFontWidth = OLEDFontWidth_16;
			_CurrentFontoffset =  OLEDFontOffset_Minus;
			_CurrentFontheight = OLEDFontHeight_16;
			_CurrentFontLength = OLEDFontLenNumeric;
		break;
		case OLEDFont_ArialRound: // Arial round 16 by 24
			_CurrentFontWidth = OLEDFontWidth_16;
			_CurrentFontoffset = OLEDFontOffset_Space;
			_CurrentFontheight = OLEDFontHeight_24;
			_CurrentFontLength = OLEDFontLenAlphaNum;
		break;
		case OLEDFont_ArialBold: // Arial bold  16 by 16
			_CurrentFontWidth = OLEDFontWidth_16;
			_CurrentFontoffset = OLEDFontOffset_Space;
			_CurrentFontheight = OLEDFontHeight_16;
			_CurrentFontLength = OLEDFontLenAlphaNum;
		break;
		case OLEDFont_Mia: // mia  8 by 16
			_CurrentFontWidth = OLEDFontWidth_8;
			_CurrentFontoffset = OLEDFontOffset_Space;
			_CurrentFontheight = OLEDFontHeight_16;
			_CurrentFontLength = OLEDFontLenAlphaNum;
		break;
		case OLEDFont_Dedica: // dedica  6 by 12
			_CurrentFontWidth = OLEDFontWidth_6;
			_CurrentFontoffset = OLEDFontOffset_Space;
			_CurrentFontheight = OLEDFontHeight_12;
			_CurrentFontLength = OLEDFontLenAlphaNum;
		break;
		default: // if wrong font num passed in,  set to default
			_CurrentFontWidth = OLEDFontWidth_5;
			_CurrentFontoffset =  OLEDFontOffset_Extend;
			_CurrentFontheight = OLEDFontHeight_8;
			_CurrentFontLength = OLEDFontLenAlphaNum;
			_FontNumber = OLEDFont_Default;
		break;
	}
}

/*!
	@brief writes a character on the OLED
	@param x X coordinate
	@param y Y coordinate
	@param character The ASCII character
	@param color 
	@param bg background color
	@return OLED_Return_Codes_e
	@note for font 7-12 only
*/
OLED_Return_Codes_e SSD1306_graphics::drawChar(uint8_t x, uint8_t y, uint8_t character, uint8_t color , uint8_t bg) 
{
	uint8_t FontSizeMod = 0;
	// Check user input
	// 1. Check for wrong font
	switch (_FontNumber)
	{
		case OLEDFont_Bignum:
		case OLEDFont_Mednum:
		case OLEDFont_ArialRound:
		case OLEDFont_ArialBold:
			FontSizeMod  = 2;
		break;
		case OLEDFont_Mia:
		case OLEDFont_Dedica:
			FontSizeMod  = 1;
		break;
		default:
			printf("Error drawChar 4: Wrong font selected, must be font 7-12: %u \r\n",  OLED_WrongFont);
			return OLED_WrongFont;
		break;
	}
	// 2. Check for character out of font bounds
	if ( character < _CurrentFontoffset || character >= (_CurrentFontLength+ _CurrentFontoffset))
	{
		printf("Error drawChar 3: Character out of Font bounds : %u :  %u  %u<->%u \r\n",OLED_CharFontASCIIRange, character,_CurrentFontoffset, (_CurrentFontLength + _CurrentFontoffset));
		return OLED_CharFontASCIIRange;
	}
	// 3. Check for screen out of  bounds
	if((x >= _width)            || // Clip right
	(y >= _height)           || // Clip bottom
	((x + _CurrentFontWidth+1) < 0) || // Clip left
	((y + _CurrentFontheight) < 0))   // Clip top
	{
		printf( "Error drawChar 3: Co-ordinates out of bounds: %u  \r\n", OLED_CharScreenBounds);
		return OLED_CharScreenBounds;
	}
	
	uint8_t i, j;
	uint8_t ctemp = 0, y0 = y; 

	for (i = 0; i < _CurrentFontheight*FontSizeMod; i++) 
	{
		switch (_FontNumber)
		{
			case OLEDFont_Bignum: ctemp = pFontBigNumptr[character - _CurrentFontoffset][i]; break;
			case OLEDFont_Mednum: ctemp = pFontMedNumptr[character - _CurrentFontoffset][i]; break;
			case OLEDFont_ArialRound: ctemp = pFontArial16x24ptr[character - _CurrentFontoffset][i]; break;
			case OLEDFont_ArialBold: ctemp = pFontArial16x16ptr[character - _CurrentFontoffset][i]; break;
			case OLEDFont_Mia: ctemp = pFontMia8x16ptr[character - _CurrentFontoffset][i]; break;
			case OLEDFont_Dedica: ctemp = pFontDedica8x12ptr[character - _CurrentFontoffset][i]; break;
			default :
				printf("Error drawChar 4: Wrong font selected, must be font 7-12 : %u\r\n",  OLED_WrongFont);
				return OLED_WrongFont;
			break;
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
	return OLED_Success;
}

/*!
	@brief Writes text string (*ptext) on the OLED
	@param x X coordinate
	@param y Y coordinate
	@param pText pointer to string of ASCII character's
	@param color text color
	@param bg background color
	@return OLED_Return_Codes_e enum
	@note for font 7-12 only
*/
OLED_Return_Codes_e SSD1306_graphics::drawText(uint8_t x, uint8_t y, 
						char *pText, uint8_t color, uint8_t bg) 
{
	OLED_Return_Codes_e DrawCharReturnCode;
	// Check correct font number
	if (_FontNumber < OLEDFont_Bignum)
	{
		printf("Error drawText 1 :Wrong font selected, must be 7 -12: %u \n",  OLED_WrongFont);
		return OLED_WrongFont;
	}

	// Check for null pointer
	if(pText == nullptr)
	{
		printf("Error drawText 2 :String array is not valid pointer: %u \n", OLED_CharArrayNullptr);
		return OLED_CharArrayNullptr;
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
		DrawCharReturnCode = drawChar(x, y, *pText, color, bg);
		if(DrawCharReturnCode  != OLED_Success)
		{
			printf("Error drawText 3: Method drawChar failed: %u\n", DrawCharReturnCode);
			return DrawCharReturnCode;
		}
		x += _CurrentFontWidth ;
		pText++;
	}
	return OLED_Success;
}


/*!
	@brief Writes text string on the OLED
	@param x X coordinate
	@param y Y coordinate
	@param pText pointer to string/array
	@param color text color
	@param bg background color
	@param size 1-x
	@return OLED_Return_Codes_e enum
	@note for font #1-6 only
*/
OLED_Return_Codes_e SSD1306_graphics::drawText(uint8_t x, uint8_t y, char *pText, uint8_t color, uint8_t bg, uint8_t size) 
{
	// check Correct font number
	if (_FontNumber >= OLEDFont_Bignum)
	{
		printf("Error drawText 1: Wrong font number , must be 1-6 %u\n", OLED_WrongFont);
		return OLED_WrongFont;
	}
	// Check for null pointer
	if(pText == nullptr)
	{
		printf("Error drawText 2: String array is not valid pointer: %u \n", OLED_CharArrayNullptr);
		return OLED_CharArrayNullptr;
	}
	OLED_Return_Codes_e DrawCharReturnCode;
	uint8_t lcursor_x = x; 
	uint8_t lcursor_y = y;

	while (*pText != '\0') 
	{
		if (_textwrap && ((lcursor_x + size * _CurrentFontWidth) > _width)) 
		{
			lcursor_x = 0;
			lcursor_y = lcursor_y + size * 7 + 3;
			if (lcursor_y > _height) lcursor_y = _height;
		}
		DrawCharReturnCode = drawChar(lcursor_x, lcursor_y, *pText, color, bg, size);
		if (DrawCharReturnCode != OLED_Success)
		{
			printf("Error drawText 3: Method drawChar failed: %u\n", DrawCharReturnCode);
			return DrawCharReturnCode;
		};
		lcursor_x = lcursor_x + size * (_CurrentFontWidth + 1);
		if (lcursor_x > _width) lcursor_x = _width;
		pText++;
	}
	return OLED_Success;
}
