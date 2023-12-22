/*!
	@file SSD1306_OLED_RPI/examples/src/CLOCK_DEMO/main.cpp
	@author Gavin Lyons
	@brief Test file for SSD1306_OLED library, Test file showing a "clock demo" 128X64 screen 
	Project Name: SSD1306_OLED_RPI
	
	@details One possible method you can also use strings objects
	
	@test
		-# Test 401 Clock Demo
*/

#include <bcm2835.h>
#include <time.h>
#include <stdio.h>

#include "SSD1306_OLED.hpp"
#include "Bitmap_test_data.hpp" // Test data for bitmaps

#define myOLEDwidth  128
#define myOLEDheight 64
uint8_t fullscreenBuffer[myOLEDwidth * (myOLEDheight/8)]; //1024  128 * 64/8
SSD1306 myOLED(myOLEDwidth ,myOLEDheight) ; // instantiate  an object

// =============== Function prototype ================
bool SetupTest(void);
void Test(void);
void EndTests(void);
void DisplayClock(void);
void SplashScreen(void);

// ======================= Main ===================
int main(int argc, char **argv)
{
	if (SetupTest() != true) return -1;
	Test();
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
	bcm2835_close(); // Close the library
	printf("OLED Test End\r\n");
}


void Test()
{
	SplashScreen();  
	DisplayClock();  
}


void DisplayClock(void)
{

	time_t now;
	struct tm *timenow;
	char displayStr[10]={};
	myOLED.setTextColor(WHITE);
	int count =0;
	printf("OLED Clock Demo 100 seconds.\r\n");
	while(count <100)
	{
		time(&now);
		timenow = localtime(&now);
		
		myOLED.OLEDBitmap(0, 0, 16, 8,  SignalIcon, false);
		myOLED.OLEDBitmap(20, 0, 16, 8,  MsgIcon, false);
		myOLED.OLEDBitmap(37, 0, 8, 8,  AlarmIcon, false);
		myOLED.OLEDBitmap(110, 0, 16, 8,  BatIcon, false);
		
		myOLED.drawLine(0,10,128,10,WHITE);
		myOLED.drawLine(0,35,128,35,WHITE);
		myOLED.drawLine(0,63,128,63,WHITE);
		
		myOLED.drawLine(0,10,0,63,WHITE);
		myOLED.drawLine(127,10,127,63,WHITE);
		
		myOLED.drawLine(40,35,40,63,WHITE);
		myOLED.drawLine(75,35,75,63,WHITE);
		
		myOLED.setFontNum(OLEDFontType_Default);
		myOLED.setTextSize(2);
		myOLED.setCursor(20,17);
		sprintf(displayStr, "%i%i:%i%i:%i%i",timenow->tm_hour / 10,
				timenow->tm_hour % 10, timenow->tm_min / 10,
				timenow->tm_min % 10,timenow->tm_sec / 10,timenow->tm_sec % 10);
		myOLED.print(displayStr);
		
		myOLED.setFontNum(OLEDFontType_Default);
		myOLED.setTextSize(1);
		myOLED.setCursor(5,44);
		sprintf(displayStr, "%i%i/%i%i",timenow->tm_mday / 10,timenow->tm_mday % 10, timenow->tm_mon / 10,timenow->tm_mon % 10);
		myOLED.print(displayStr);
		
		myOLED.setCursor(55,44);
		myOLED.print(count);
		
		myOLED.OLEDBitmap(80, 40, 16, 8,  MsgIcon, false); 
		myOLED.OLEDBitmap(100, 40, 16, 8, MsgIcon, true);
		bcm2835_delay(1000);
		myOLED.OLEDupdate();
		myOLED.OLEDclearBuffer();
		count++;
	}
	
	bcm2835_delay(5000);
	myOLED.OLEDFillScreen(0x00, 0);
	myOLED.OLEDclearBuffer();

}


void SplashScreen(void)
{
	myOLED.buffer = (uint8_t*) &fullscreenBuffer;
	if(myOLED.buffer == nullptr) // check if pointer is still = null
	{
		printf("Error 1203 :: Problem assigning buffer pointer\r\n");
		exit(-1);
	}
	myOLED.OLEDBitmap(0, 0, myOLEDwidth, myOLEDheight, fullscreenBitmap, true);
	myOLED.OLEDupdate();
	bcm2835_delay(5000);
	myOLED.OLEDFillScreen(0x00, 0);
	myOLED.OLEDclearBuffer();
}

