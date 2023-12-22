/*!
	@file SSD1306_OLED_RPI/examples/src/HELLO_WORLD/main.cpp
	@author Gavin Lyons
	@brief Test file for SSD1306_OLED library, showing  "hello world" basic use case
	Project Name: SSD1306_OLED_RPI.
	
	@test
		1. Test 100 Hello World 128x64 screen
*/

#include <bcm2835.h>
#include <time.h>
#include <stdio.h>

#include "SSD1306_OLED.hpp"

#define myOLEDwidth  128
#define myOLEDheight 64
SSD1306 myOLED(myOLEDwidth ,myOLEDheight) ; // instantiate a OLED object 

// =============== Function prototype ================
bool SetupTest(void);
void TestLoop(void);
void EndTest(void);

// ======================= Main ===================
int main(int argc, char **argv) 
{
	if (SetupTest() != true) return -1;
	TestLoop();
	EndTest();
	return 0;
}
// ======================= End of main  ===================

// ===================== Function Space =====================
bool SetupTest() 
{
	const uint16_t I2C_Speed = 626; //  bcm2835I2CClockDivider enum , see readme.
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
	
	// Turn on I2C bus (optionally it may already be on)
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

void EndTest()
{
	myOLED.OLEDPowerDown(); //Switch off display
	myOLED.OLED_I2C_OFF(); // Switch off I2C , optional may effect other programs & devices
	bcm2835_close(); // Close the library
	printf("OLED Test End\r\n");
}

void TestLoop() 
{

	// Define a buffer to cover whole screen 
	uint8_t  screenBuffer[myOLEDwidth * (myOLEDheight/8)+1]; 
	myOLED.buffer = (uint8_t*) &screenBuffer;  // set that to library buffer pointer
	if(myOLED.buffer == nullptr) // check if pointer is still = null
	{
		printf("Error 1203 :: Problem assigning buffer pointer\r\n");
		exit(-1);
	}
	myOLED.OLEDclearBuffer(); 
	myOLED.setTextColor(WHITE);
	myOLED.setCursor(10, 10);
	myOLED.print("Hello world");
	myOLED.OLEDupdate();  
	delay(5000);

}

// ============== EOF =========
