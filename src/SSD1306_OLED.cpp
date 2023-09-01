/*!
* @file SSD1306_OLED.cpp
* @brief   OLED driven by SSD1306 controller, Source file
* @author Gavin Lyons.
* @details <https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI>
*/

#include "SSD1306_OLED.hpp"
#include <stdbool.h>

/*!
	@brief init the screen object
	@param oledwidth width of OLED in pixels 
	@param oledwidth height of OLED in pixels 
 */
SSD1306  :: SSD1306(int16_t oledwidth, int16_t oledheight) :SSD1306_graphics(oledwidth, oledheight)
{
	_OLED_HEIGHT = oledheight;
	_OLED_WIDTH = oledwidth;
	_OLED_PAGE_NUM = (_OLED_HEIGHT/8); 
	bufferWidth = _OLED_WIDTH;
	bufferHeight = _OLED_HEIGHT;
}

/*!
	@brief  begin Method initialise OLED
	@param I2C_speed default = 0 , 0 = bcm2835_i2c_set_baudrate(100000) 100k baudrate,  > 0 = BCM2835_I2C_CLOCK_DIVIDER, choices = 2500 , 622 , 150 , 148
	@param I2c_address by default 0x3C
*/
void SSD1306::OLEDbegin( uint16_t I2C_speed , uint8_t I2c_address)
{
	_I2C_speed = I2C_speed;
	_I2C_address = I2c_address;
	OLED_I2C_ON();
	OLEDinit();
	OLED_I2C_OFF();
}

/*!
	@brief  Start I2C operations. Forces RPi I2C pins P1-03 (SDA) and P1-05 (SCL) 
	to alternate function ALT0, which enables those pins for I2C interface. 
*/
void SSD1306::OLED_I2C_ON()
{
	if (!bcm2835_i2c_begin())
	{
		printf("Error: Cannot start I2C, Running root?\n");
		return;
	}
	bcm2835_i2c_setSlaveAddress(_I2C_address);  //i2c address
	
	if ( _I2C_speed > 0)  
	{
		// BCM2835_I2C_CLOCK_DIVIDER enum choice  2500 622 150 148
		// Clock divided is based on nominal base clock rate of 250MHz
		bcm2835_i2c_setClockDivider(_I2C_speed);
	} else{
		// default or use set_baudrate instead of clockdivder 100k
		bcm2835_i2c_set_baudrate(100000); //100k baudrate
	}
}

/*!
	@brief End I2C operations. I2C pins P1-03 (SDA) and P1-05 (SCL) 	
	are returned to their default INPUT behaviour. 
*/
void SSD1306::OLED_I2C_OFF(void)
{
	bcm2835_i2c_end();
}

/*! 
	@brief Disables  OLED Call when powering down
*/
void SSD1306::OLEDPowerDown(void)
{
	OLEDEnable(0);
	bcm2835_delay(100);
}

/*!
	@brief Called from OLEDbegin carries out Power on sequence and register init
*/
void SSD1306::OLEDinit()
 {

	bcm2835_delay(SSD1306_INITDELAY);
	SSD1306_command( SSD1306_DISPLAY_OFF);
	SSD1306_command( SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO);
	SSD1306_command( 0x80);
	SSD1306_command( SSD1306_SET_MULTIPLEX_RATIO );
	SSD1306_command( _OLED_HEIGHT - 1 );
	SSD1306_command( SSD1306_SET_DISPLAY_OFFSET );
	SSD1306_command(0x00);
	SSD1306_command( SSD1306_SET_START_LINE|0x00);
	SSD1306_command( SSD1306_CHARGE_PUMP );
	SSD1306_command(0x14);
	SSD1306_command( SSD1306_MEMORY_ADDR_MODE );
	SSD1306_command(0x00);  //Horizontal Addressing Mode is Used
	SSD1306_command( SSD1306_SET_SEGMENT_REMAP| 0x01);
	SSD1306_command( SSD1306_COM_SCAN_DIR_DEC );

switch (_OLED_HEIGHT)
{
	case 64: 
		SSD1306_command( SSD1306_SET_COM_PINS );
		SSD1306_command( 0x12 );
		SSD1306_command( SSD1306_SET_CONTRAST_CONTROL );
		SSD1306_command(0xCF);
	break;
	case 32: 
		SSD1306_command( SSD1306_SET_COM_PINS );
		SSD1306_command( 0x02 );
		SSD1306_command( SSD1306_SET_CONTRAST_CONTROL );
		SSD1306_command(0x8F);
	break;
	case 16: // NOTE: not tested, lacking part. 
		SSD1306_command( SSD1306_SET_COM_PINS );
		SSD1306_command( 0x2 ); // ?
		SSD1306_command( SSD1306_SET_CONTRAST_CONTROL );
		SSD1306_command(0xAF);
	break;
}

	SSD1306_command( SSD1306_SET_PRECHARGE_PERIOD );
	SSD1306_command( 0xF1 );
	SSD1306_command( SSD1306_SET_VCOM_DESELECT );
	SSD1306_command( 0x40 );
	SSD1306_command( SSD1306_DISPLAY_ALL_ON_RESUME );
	SSD1306_command( SSD1306_NORMAL_DISPLAY );
	SSD1306_command( SSD1306_DEACTIVATE_SCROLL );
	SSD1306_command( SSD1306_DISPLAY_ON );

	bcm2835_delay(SSD1306_INITDELAY);
}

/*!
	@brief Turns On Display
	@param bits   1  on , 0 off
*/
void SSD1306::OLEDEnable(uint8_t bits)
{
	OLED_I2C_ON();
	bits ? SSD1306_command(SSD1306_DISPLAY_ON) : SSD1306_command(SSD1306_DISPLAY_OFF);
	OLED_I2C_OFF();
}

/*!
	@brief Adjusts contrast
	@param contrast 0x00 to 0xFF , default 0x80
*/
void SSD1306::OLEDContrast(uint8_t contrast)
{
	OLED_I2C_ON();
	SSD1306_command( SSD1306_SET_CONTRAST_CONTROL );
	SSD1306_command(contrast);
	OLED_I2C_OFF();
}

/*!
	@brief invert the display
	@param value true invert , false normal
*/
void SSD1306::OLEDInvert(bool value)
{
 OLED_I2C_ON();
 value ? SSD1306_command( SSD1306_INVERT_DISPLAY ) : SSD1306_command( SSD1306_NORMAL_DISPLAY );
 OLED_I2C_OFF();
}

/*!
	@brief Fill the screen NOT the buffer with a datapattern
	@param dataPattern can be set to zero to clear screen (not buffer) range 0x00 to 0ff
	@param delay in milliseconds can be set to zero normally.
*/
void SSD1306::OLEDFillScreen(uint8_t dataPattern, uint8_t delay)
{
	OLED_I2C_ON();
	for (uint8_t row = 0; row < _OLED_PAGE_NUM; row++)
	{
		SSD1306_command( 0xB0 | row);
		SSD1306_command(SSD1306_SET_LOWER_COLUMN);
		SSD1306_command(SSD1306_SET_HIGHER_COLUMN);
		for (uint8_t col = 0; col < _OLED_WIDTH; col++)
		{
			SSD1306_data(dataPattern);
			bcm2835_delay(delay);
		}
	}
	OLED_I2C_OFF();
}

/*!
	@brief Fill the chosen page(1-8)  with a datapattern
	@param page_num chosen page (1-8)
	@param dataPattern can be set to 0 to FF (not buffer)
	@param mydelay optional delay in milliseconds can be set to zero normally.
*/
void SSD1306::OLEDFillPage(uint8_t page_num, uint8_t dataPattern,uint8_t mydelay)
{
	OLED_I2C_ON();
	uint8_t Result =0xB0 | page_num; 
	SSD1306_command(Result);
	SSD1306_command(SSD1306_SET_LOWER_COLUMN);
	SSD1306_command(SSD1306_SET_HIGHER_COLUMN);
	uint8_t numofbytes = _OLED_WIDTH;
	for (uint8_t i = 0; i < numofbytes; i++)
	{
		SSD1306_data(dataPattern);
		bcm2835_delay(mydelay);
	}
	OLED_I2C_OFF();
}

/*!
	@brief Draw a bitmap  to the buffer 
	@param x x axis offset 0-128
	@param y y axis offset 0-64
	@param w width 0-128
	@param h height 0-64
	@param data pointer to bitmap data
	@param invert color 
	@note bitmap data must be  horizontally addressed.
*/
void SSD1306::OLEDBitmap(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t* data, bool invert)
{

int16_t byteWidth = (w + 7) / 8; 
uint8_t byte = 0;
uint8_t color, bgcolor;
if (invert == false)
{
	color = WHITE;
	bgcolor = BLACK;
}else
{
	color = BLACK;
	bgcolor = WHITE;
}

for (int16_t j = 0; j < h; j++, y++) 
{
	for (int16_t i = 0; i < w; i++) 
	{
		if (i & 7)
			byte <<= 1;
		else
			byte = data[j * byteWidth + i / 8];
			
		drawPixel(x + i, y, (byte & 0x80) ? color : bgcolor );
	}
}

}

/*!
	@brief Writes a byte to I2C address,command or data, used internally
	@param value write the value to be written
	@param cmd command or data
	@note In the event of an error will loop 3 times each time.
	Printing the error code , see bcm2835I2CReasonCodes in bcm2835 docs.
*/
void SSD1306::I2C_Write_Byte(uint8_t value, uint8_t cmd)
{
	char buf[2] = {cmd,value};
	uint8_t attemptI2Cwrite = 0;
	uint8_t returnCode = 0;
	
	returnCode = bcm2835_i2c_write(buf, 2); 
	
	while(returnCode != 0)
	{ // failure to write I2C byte 
		attemptI2Cwrite ++;
		printf("Error I2C: Cannot Write byte :: %u\n", attemptI2Cwrite);
		printf("bcm2835I2CReasonCodes :: Error code %u\n", returnCode);
		returnCode  = bcm2835_i2c_write(buf, 2);
		bcm2835_delay(100); // mS
		if (attemptI2Cwrite >= 3) break;
	}
}

/*!
	@brief updates the buffer i.e. writes it to the screen
*/
void SSD1306::OLEDupdate()
{
	uint8_t x = 0; uint8_t y = 0; uint8_t w = this->bufferWidth; uint8_t h = this->bufferHeight;
	OLEDBuffer( x,  y,  w,  h, (uint8_t*) this->buffer);
}

/*!
	@brief clears the buffer memory i.e. does NOT write to the screen
*/
void SSD1306::OLEDclearBuffer()
{

	memset( this->buffer, 0x00, (this->bufferWidth * (this->bufferHeight /8))  );

}

/*!
	@brief Draw a bitmap directly to the screen
	@param x x axis  offset 0-128
	@param y y axis offset 0-64
	@param w width 0-128
	@param h height 0-64
	@param data the buffer data
	@note Called by OLEDupdate internally 
*/
void SSD1306::OLEDBuffer(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t* data)
{
	OLED_I2C_ON();
	uint8_t tx, ty;
	uint16_t offset = 0;
		
	SSD1306_command( SSD1306_SET_COLUMN_ADDR );
	SSD1306_command(0);   // Column start address (0 = reset)
	SSD1306_command( _OLED_WIDTH-1 ); // Column end address (127 = reset)

	SSD1306_command( SSD1306_SET_PAGE_ADDR );
	SSD1306_command(0); // Page start address (0 = reset)
	
	switch (_OLED_HEIGHT)
	{
		case 64: SSD1306_command(7); break;
		case 32: SSD1306_command(3); break;
		case 16: SSD1306_command(1); break;
	}
	
	for (ty = 0; ty < h; ty = ty + 8)
		{
		if (y + ty < 0 || y + ty >= _OLED_HEIGHT) {continue;}
		for (tx = 0; tx < w; tx++)
		{

			if (x + tx < 0 || x + tx >= _OLED_WIDTH) {continue;}
			offset = (w * (ty /8)) + tx;
			SSD1306_data(data[offset++]);
		}
	}
	OLED_I2C_OFF();

}

/*!
	@brief Draws a Pixel to the screen overides the gfx lib if defined
	@param x x axis  position  
	@param y y axis  position
	@param color color of pixel.
*/
void SSD1306::drawPixel(int16_t x, int16_t y, uint8_t color)
{

	if ((x < 0) || (x >= this->bufferWidth) || (y < 0) || (y >= this->bufferHeight)) {
	return;
	}
	int16_t temp;
	switch (rotation) {
	case 1:
		temp = x;
		x = WIDTH - 1 - y;
		y = temp;
	break;
	case 2:
		x = WIDTH - 1 - x;
		y = HEIGHT - 1 - y;
	break;
	case 3:
		temp = x;
		x = y;
		y = HEIGHT - 1 - temp;
	break;
	}
		uint16_t tc = (bufferWidth * (y /8)) + x;
		switch (color)
		{
			case WHITE:  this->buffer[tc] |= (1 << (y & 7)); break;
			case BLACK:  this->buffer[tc] &= ~(1 << (y & 7)); break;
			case INVERSE: this->buffer[tc] ^= (1 << (y & 7)); break;
		}
}

/*!
	@brief Scroll OLED data to the right
	@param start start position
	@param stop stop position 
*/
void SSD1306::OLED_StartScrollRight(uint8_t start, uint8_t stop) 
{
	OLED_I2C_ON();
	SSD1306_command(SSD1306_RIGHT_HORIZONTAL_SCROLL);
	SSD1306_command(0X00);
	SSD1306_command(start);  // start page
	SSD1306_command(0X00);
	SSD1306_command(stop);   // end page
	SSD1306_command(0X00);
	SSD1306_command(0XFF);
	SSD1306_command(SSD1306_ACTIVATE_SCROLL);
	OLED_I2C_OFF();
}

/*!
	@brief Scroll OLED data to the left
	@param start start position
	@param stop stop position 
*/
void SSD1306::OLED_StartScrollLeft(uint8_t start, uint8_t stop) 
{
	OLED_I2C_ON();
	SSD1306_command(SSD1306_LEFT_HORIZONTAL_SCROLL);
	SSD1306_command(0X00);
	SSD1306_command(start);
	SSD1306_command(0X00);
	SSD1306_command(stop);
	SSD1306_command(0X00);
	SSD1306_command(0XFF);
	SSD1306_command(SSD1306_ACTIVATE_SCROLL);
	OLED_I2C_OFF();
}

/*!
	@brief Scroll OLED data diagonally to the right
	@param start start position
	@param stop stop position 
*/
void SSD1306::OLED_StartScrollDiagRight(uint8_t start, uint8_t stop) 
{
	OLED_I2C_ON();
	SSD1306_command(SSD1306_SET_VERTICAL_SCROLL_AREA);
	SSD1306_command(0X00);
	SSD1306_command(_OLED_HEIGHT);
	SSD1306_command(SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL);
	SSD1306_command(0X00);
	SSD1306_command(start);
	SSD1306_command(0X00);
	SSD1306_command(stop);
	SSD1306_command(0X01);
	SSD1306_command(SSD1306_ACTIVATE_SCROLL);
	OLED_I2C_OFF();
}

/*!
	@brief Scroll OLED data diagonally to the left
	@param start start position
	@param stop stop position 
*/
void SSD1306::OLED_StartScrollDiagLeft(uint8_t start, uint8_t stop) 
{
	OLED_I2C_ON();
	SSD1306_command(SSD1306_SET_VERTICAL_SCROLL_AREA);
	SSD1306_command(0X00);
	SSD1306_command(_OLED_HEIGHT);
	SSD1306_command(SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL);
	SSD1306_command(0X00);
	SSD1306_command(start);
	SSD1306_command(0X00);
	SSD1306_command(stop);
	SSD1306_command(0X01);
	SSD1306_command(SSD1306_ACTIVATE_SCROLL);
	OLED_I2C_OFF();
}

/*!
	@brief  Stop scroll mode
*/
void SSD1306::OLED_StopScroll(void) 
{
	OLED_I2C_ON();
	SSD1306_command(SSD1306_DEACTIVATE_SCROLL);
	OLED_I2C_OFF();
}


// ---  EOF ---
