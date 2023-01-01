/*
* Project Name: SSD1306_OLED_RPI
* Author: Gavin Lyons.
* URL: https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI
*/
  
#ifndef _SSD1306_OLED_H_
#define _SSD1306_OLED_H_

// ************** Library INCLUDES ********
#include <bcm2835.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "SSD1306_OLED_graphics.hpp"

// ********* DEFINES ********
// ***********  SSD1306 Command Set  ***********

// Fundamental Commands
#define SSD1306_SET_CONTRAST_CONTROL                    0x81
#define SSD1306_DISPLAY_ALL_ON_RESUME                   0xA4
#define SSD1306_DISPLAY_ALL_ON                          0xA5
#define SSD1306_NORMAL_DISPLAY                          0xA6
#define SSD1306_INVERT_DISPLAY                          0xA7
#define SSD1306_DISPLAY_OFF                             0xAE
#define SSD1306_DISPLAY_ON                              0xAF
#define SSD1306_NOP                                     0xE3

// Scrolling Commands
#define SSD1306_RIGHT_HORIZONTAL_SCROLL                 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL                  0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL    0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL     0x2A
#define SSD1306_DEACTIVATE_SCROLL                       0x2E
#define SSD1306_ACTIVATE_SCROLL                         0x2F
#define SSD1306_SET_VERTICAL_SCROLL_AREA                0xA3

// Addressing Setting Commands
#define SSD1306_SET_LOWER_COLUMN                        0x00
#define SSD1306_SET_HIGHER_COLUMN                       0x10
#define SSD1306_MEMORY_ADDR_MODE                        0x20
#define SSD1306_SET_COLUMN_ADDR                         0x21
#define SSD1306_SET_PAGE_ADDR                           0x22

// Hardware Configuration Commands
#define SSD1306_SET_START_LINE                          0x40
#define SSD1306_SET_SEGMENT_REMAP                       0xA0
#define SSD1306_SET_MULTIPLEX_RATIO                     0xA8
#define SSD1306_COM_SCAN_DIR_INC                        0xC0
#define SSD1306_COM_SCAN_DIR_DEC                        0xC8
#define SSD1306_SET_DISPLAY_OFFSET                      0xD3
#define SSD1306_SET_COM_PINS                            0xDA
#define SSD1306_CHARGE_PUMP                             0x8D

// Timing & Driving Scheme Setting Commands
#define SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO             0xD5
#define SSD1306_SET_PRECHARGE_PERIOD                    0xD9
#define SSD1306_SET_VCOM_DESELECT                       0xDB

// I2C related
#define SSD1306_COMMAND                     0x00
#define SSD1306_DATA                        0xC0
#define SSD1306_DATA_CONTINUE               0x40
#define SSD1306_ADDR                        0x3C // alt 0x3D
#define SSD1306_command(Reg)  I2C_Write_Byte(Reg, SSD1306_COMMAND)
#define SSD1306_data(Data)    I2C_Write_Byte(Data, SSD1306_DATA_CONTINUE)

#define BLACK                 0
#define WHITE                 1
#define INVERSE               2

// Delays
#define SSD1306_INITDELAY 100 // mS


// *********** CLASS SECTION ***********8
class SSD1306 : public SSD1306_graphics  {
  public:
	SSD1306(int16_t oledwidth, int16_t oledheight);
	~SSD1306(){};

	uint8_t* buffer = nullptr;

	virtual void drawPixel(int16_t x, int16_t y, uint8_t color) override;
	void OLEDupdate(void);
	void OLEDclearBuffer(void);
	void OLEDBuffer(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t* data);
	void OLEDFillScreen(uint8_t pixel, uint8_t mircodelay);
	void OLEDFillPage(uint8_t page_num, uint8_t pixels,uint8_t delay);
	void OLEDBitmap(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t* data, bool invert);
	
	void OLEDbegin(uint16_t I2C_speed = 0, uint8_t I2c_address= SSD1306_ADDR );
	void OLEDinit(void);
	void OLEDReset(void);
	void OLEDPowerDown(void);
	
	void OLEDEnable(uint8_t on);
	void OLEDContrast(uint8_t OLEDcontrast);
	void OLEDInvert(bool on);
	
	void OLED_StartScrollRight(uint8_t start, uint8_t stop); 
	void OLED_StartScrollLeft(uint8_t start, uint8_t stop) ;
	void OLED_StartScrollDiagRight(uint8_t start, uint8_t stop) ;
	void OLED_StartScrollDiagLeft(uint8_t start, uint8_t stop) ;
	void OLED_StopScroll(void) ;
	

  private:

	void I2C_Write_Byte(uint8_t value, uint8_t Cmd);
	void OLED_I2C_OFF(void);
	void OLED_I2C_ON(void);
	uint16_t _I2C_speed = 0 ;
	uint8_t _I2C_address = SSD1306_ADDR ;
	
	int16_t _OLED_WIDTH;
	int16_t _OLED_HEIGHT;
	int8_t _OLED_PAGE_NUM;
	uint8_t bufferWidth ;
	uint8_t bufferHeight ;

}; // end of class

#endif // end of guard header

