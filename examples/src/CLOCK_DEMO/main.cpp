/*!
	@file SSD1306_OLED_RPI/examples/src/CLOCK_DEMO/main.cpp
	@author Gavin Lyons
	@brief Test file for SSD1306_OLED library, Test file showing a "clock demo" 128X64 screen
	Project Name: SSD1306_OLED_RPI
	@test
		-# Test 401 Clock Demo
*/

#include <iostream>
#include <ctime>
#include <bcm2835.h>
#include <csignal> //catch user Ctrl+C
#include "SSD1306_OLED.hpp"
#include "Bitmap_test_data.hpp" // Test data for bitmaps

#define myOLEDwidth  128
#define myOLEDheight 64
#define FULLSCREEN (myOLEDwidth * (myOLEDheight/8))
uint8_t screenBuffer[FULLSCREEN];
SSD1306 myOLED(myOLEDwidth ,myOLEDheight) ; // instantiate  an object

// =============== Function prototype ================
bool SetupTest(void);
void Test(void);
void EndTests(void);
void DisplayClock(void);
void SplashScreen(void);
std::string UTC_string(void);
void signal_callback_handler(int signum);

// ======================= Main ===================
int main()
{
	signal(SIGINT, signal_callback_handler);
	if (SetupTest() != true) return -1;
	Test();
	EndTests();
	return 0;
}
// ======================= End of Main ===================


// ======================= Function space ===================
bool SetupTest()
{
	const uint16_t I2C_Speed = BCM2835_I2C_CLOCK_DIVIDER_626; //  bcm2835I2CClockDivider enum , see readme.
	const uint8_t I2C_Address = 0x3C;
	bool I2C_debug = false;
	std::cout<<"OLED Test Begin" << std::endl;

	// Check if Bcm28235 lib installed and print version.
	if(!bcm2835_init())
	{
		std::cout<<"Error 1201: init bcm2835 library , Is it installed ?"<< std::endl;
		return false;
	}

	// Turn on I2C bus (optionally it may already be on)
	if(!myOLED.OLED_I2C_ON())
	{
		std::cout<<"Error 1202: bcm2835_i2c_begin :Cannot start I2C, Running as root?"<< std::endl;
		bcm2835_close(); // Close the library
		return false;
	}

	std::cout<<"SSD1306 library Version Number :: " << myOLED.getLibVerNum() << std::endl;
	std::cout<<"bcm2835 library Version Number :: "  << bcm2835_version()    << std::endl;
	bcm2835_delay(500);
	myOLED.OLEDbegin(I2C_Speed, I2C_Address, I2C_debug); // initialize the OLED
	return true;
}

void EndTests()
{
	myOLED.OLEDPowerDown(); //Switch off display
	myOLED.OLED_I2C_OFF(); // Switch off I2C , optional may effect other programs & devices
	bcm2835_close(); // Close the library
	std::cout<<"OLED Test End" << std::endl;
}

void Test()
{
	if (!myOLED.OLEDSetBufferPtr(myOLEDwidth, myOLEDheight, screenBuffer, sizeof(screenBuffer))) return;
	SplashScreen();
	DisplayClock();
}

void DisplayClock(void)
{
	myOLED.setTextColor(WHITE);
	uint16_t count =0;
	std::cout<<"OLED Clock Demo :: Press Ctrl + c to quit." << std::endl;
	while(count < 9999)
	{
		std::string TimeString = UTC_string();
		std::cout<< TimeString << "\r" << std::flush;
		auto DateInfo = TimeString.substr(0, 10);
		auto TimeInfo = TimeString.substr(11,8);

		myOLED.OLEDBitmap(0, 0, 16, 8,  SignalIcon, false);
		myOLED.OLEDBitmap(20, 0, 16, 8,  MsgIcon, false);
		myOLED.OLEDBitmap(37, 0, 8, 8,  AlarmIcon, false);
		myOLED.OLEDBitmap(110, 0, 16, 8,  BatIcon, false);

		myOLED.drawLine(0,10,128,10,WHITE);
		myOLED.drawLine(0,35,128,35,WHITE);
		myOLED.drawLine(0,63,128,63,WHITE);

		myOLED.drawLine(0,10,0,63,WHITE);
		myOLED.drawLine(127,10,127,63,WHITE);

		myOLED.drawLine(75,35,75,63,WHITE);

		myOLED.setFontNum(OLEDFont_Default);
		myOLED.setTextSize(2);
		myOLED.setCursor(20,17);
		myOLED.print(TimeInfo);

		myOLED.setTextSize(1);
		myOLED.setCursor(5,44);
		myOLED.print(DateInfo);

		myOLED.setCursor(90,54);
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
	myOLED.OLEDBitmap(0, 0, myOLEDwidth, myOLEDheight, fullscreenBitmap, true);
	myOLED.OLEDupdate();
	bcm2835_delay(3000);
	myOLED.OLEDFillScreen(0x00, 0);
	myOLED.OLEDclearBuffer();
}

//Return UTC time as a std:.string with format "yyyy-mm-dd hh:mm:ss".
std::string UTC_string() 
{
	std::time_t time = std::time({});
	char timeString[std::size("yyyy-mm-dd hh:mm:ss UTC")];
	std::strftime(std::data(timeString), std::size(timeString), "%F %T UTC", std::gmtime(&time));
	return timeString;
}

// Terminate program on ctrl + C 
void signal_callback_handler(int signum)
{
	EndTests();
	exit(signum);
}
