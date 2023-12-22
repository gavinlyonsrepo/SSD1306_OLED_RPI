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
uint8_t fullscreenBuffer[myOLEDwidth * (myOLEDheight/8)]; // buffer 1024 = 128 * 64/8
SSD1306 myOLED(myOLEDwidth ,myOLEDheight) ; // instantiate  an object

// =============== Function prototype ================
bool SetupTest(void);
void EndTests(void);
void myTests(void);
void Test301(void);
void Test302(void);
void Test303(void);

void EndTests(void);

// ======================= Main ===================
int main(int argc, char **argv)
{
	if (SetupTest() != true) return -1;
	myTests();
	EndTests();
	return 0;
}
// ======================= End of Main ===================


// ======================= Function space ===================
bool SetupTest() 
{
	const uint16_t I2C_Speed = 626; // bcm2835I2CClockDivider enum ,see readme.
	const uint8_t I2C_Address = 0x3C;
	bool I2C_debug = false;
	
	printf("OLED Test Begin\r\n");
	printf("SSD1306 library Version Number :: %u\r\n",myOLED.getLibVerNum());
	
	// Check if Bcm28235 lib installed and print version.
	if(!bcm2835_init())
	{
		printf("Error 1201: init bcm2835 library , Is it installed ?\r\n");
		return false;
	}else
	{
		printf("bcm2835 library Version Number :: %u\r\n",bcm2835_version());
		bcm2835_delay(100);
	}
	
	// Turn on I2C bus (optional it may already be on)
	while(myOLED.OLED_I2C_ON() != true)
	{
		printf("Error 1202: bcm2835_i2c_begin :Cannot start I2C, Running as root?\n");
		bcm2835_delay(1500);
	}
	
	myOLED.OLEDbegin(I2C_Speed, I2C_Address, I2C_debug); // initialize the OLED
	myOLED.OLEDFillScreen(0xF0, 0); // splash screen bars, optional just for effect
	bcm2835_delay(1000);
	return true;
}


void EndTests()
{
	myOLED.OLEDPowerDown(); //Switch off display
	myOLED.OLED_I2C_OFF(); // Switch off I2C , optional may effect other programs & devices
	bcm2835_close(); // Close the bcm2835 library
	printf("OLED Test End\r\n");
}

void myTests()
{
	Test301();  
	Test302();  
	Test303();  
}


void Test301(void)
{
	printf("OLED Test 301 64x64 pixel Image\r\n");
	myOLED.buffer = (uint8_t*) &fullscreenBuffer; // buffer to the pointer
	if(myOLED.buffer == nullptr) // check if pointer is still = null
	{
		printf("Error 1203 :: Problem assigning buffer pointer\r\n");
		exit(-1);
	}
	
	myOLED.OLEDBitmap(0, 0 , 64, 64, bigImage, false);
	myOLED.OLEDupdate();
	
	bcm2835_delay(5000);
	myOLED.OLEDFillScreen(0x00, 0);
	myOLED.OLEDclearBuffer();
}

void Test302(void)
{
	printf("OLED Test 302 16x8 pixel Images , one inverted \r\n");
	myOLED.OLEDBitmap(70, 10, 16, 8,  SignalIcon, false);
	myOLED.OLEDBitmap(40, 10, 16, 8,  SignalIcon, true);
	myOLED.OLEDupdate();
	
	bcm2835_delay(5000);
	myOLED.OLEDFillScreen(0x00, 0);
	myOLED.OLEDclearBuffer();

}

void Test303(void)
{
	printf("OLED Test 303 128x64 pixel image, inverted color\r\n");
	myOLED.OLEDBitmap(0, 0, myOLEDwidth, myOLEDheight, fullscreenBitmap, true);
	myOLED.OLEDupdate();
	
	bcm2835_delay(5000);
	myOLED.OLEDFillScreen(0x00, 0);
}

