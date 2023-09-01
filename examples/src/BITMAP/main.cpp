/*!
	@file SSD1306_OLED_RPI/examples/src/BITMAP/main.cpp
	@author Gavin Lyons
	@brief Test file for SSD1306_OLED library, showing how to use  bitmap 128X64 screen 
	
	Project Name: SSD1306_OLED_RPI
	
	@test
		-# Test 301 bigImage 64x64 pixels
		-# Test 302 Small icons 16x8 pixels
		-# Test 303 full screen image 128x64 pixels 
*/

#include <bcm2835.h>
#include <time.h>
#include <stdio.h>
#include "SSD1306_OLED.hpp"
#include "Bitmap_test_data.hpp"

#define myOLEDwidth  128
#define myOLEDheight 64
uint8_t fullscreenBuffer[1024]; // buffer
const uint16_t I2C_Speed = 626; //  bcm2835I2CClockDivider, see readme
const uint8_t I2C_Address = 0x3C;
SSD1306 myOLED(myOLEDwidth ,myOLEDheight) ; // instantiate  an object

// =============== Function prototype ================
int8_t  setup(void);
void myLoop(void);
void Test303(void);
void Test302(void);
void Test301(void);
void EndTests(void);

// ======================= Main ===================
int main(int argc, char **argv)
{
	if (!setup()){return -1;}
	myLoop();
	EndTests();
	return 0;
}
// ======================= End of Main ===================


// ======================= Function space ===================
void EndTests()
{
	myOLED.OLEDPowerDown(); //Switch off display
	bcm2835_close(); // Close the library
	printf("OLED End\r\n");
}

int8_t setup()
{
	if(!bcm2835_init())
	{
		printf("Error 1201 Cannot init bcm2835 library\n");
		return -1;
	}
	bcm2835_delay(50);
	printf("OLED Begin\r\n");
	myOLED.OLEDbegin(I2C_Speed, I2C_Address); // initialize the OLED
	myOLED.OLEDFillScreen(0x01, 0); //splash screen
	bcm2835_delay(1500);
	return 1;
}

void myLoop()
{
	Test301();  
	Test302();  
	Test303();  
}


void Test301(void)
{
	myOLED.buffer = (uint8_t*) &fullscreenBuffer; // buffer to the pointer
	myOLED.OLEDBitmap(0, 0 , 64, 64, bigImage, false);
	myOLED.OLEDupdate();
	
	bcm2835_delay(5000);
	myOLED.OLEDFillScreen(0x00, 0);
	myOLED.OLEDclearBuffer();
}

void Test302(void)
{
	myOLED.OLEDBitmap(30, 10, 16, 8, MsgIcon, true);
	myOLED.OLEDBitmap(70, 10, 16, 8,  SignalIcon, false);
	myOLED.OLEDupdate();
	
	bcm2835_delay(5000);
	myOLED.OLEDFillScreen(0x00, 0);
	myOLED.OLEDclearBuffer();

}

void Test303(void)
{
	myOLED.OLEDBitmap(0, 0, myOLEDwidth, myOLEDheight, fullscreenBitmap, true);
	myOLED.OLEDupdate();
	
	bcm2835_delay(5000);
	myOLED.OLEDFillScreen(0x00, 0);
}

