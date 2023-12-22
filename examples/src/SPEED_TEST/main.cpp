

/*!
	@file SSD1306_OLED_RPI/examples/src/SPEED_TEST/main.cpp
	@author Gavin Lyons
	@brief Test file for SSD1306_OLED library,  showing fps frame rate per second
	
	Project Name: SSD1306_OLED_RPI
	
	@test
		-# Test 601 FPS test frame rate per second
		
	@details
		-# results data for test file
		-# I2C_Speed = 0 Fps 7 bcm2835_i2c_set_baudrate(100000) 
		-# I2C_Speed = 2500 Fps 6 bcm2835_i2c_setClockDivider(BCM2835_I2C_CLOCK_DIVIDER_2500) 
		-# I2C_Speed = 626 Fps 16 bcm2835_i2c_setClockDivider(BCM2835_I2C_CLOCK_DIVIDER_626) 
		-# I2C_Speed = 150 Fps 24 bcm2835_i2c_setClockDivider(BCM2835_I2C_CLOCK_DIVIDER_150) 
		-# I2C_Speed = 148 FPS 25 bcm2835_i2c_setClockDivider(BCM2835_I2C_CLOCK_DIVIDER_148) 
*/

#include <time.h>
#include <stdio.h>
#include <bcm2835.h>
#include "SSD1306_OLED.hpp"

#define myOLEDwidth  128
#define myOLEDheight 64
SSD1306 myOLED(myOLEDwidth ,myOLEDheight) ; // instantiate  an object

// vars for the test
uint16_t count  = 0;
bool colour = 1;
uint64_t  previousCounter =0;
uint8_t  screenBuffer[myOLEDwidth * (myOLEDheight / 8) ]; 

// =============== Function prototype ================
bool SetupTest(void); 
void myLoop(void);
void display_buffer(long , int );
void EndTests(void);
static uint64_t counter( void );

	
// ======================= Main ===================
int main(int argc, char **argv)
{

	if (SetupTest() != true) return -1;
	myLoop();
	EndTests();
	return 0;
}
// ======================= End of main  ===================

void EndTests()
{
	myOLED.OLEDPowerDown(); //Switch off display
	myOLED.OLED_I2C_OFF(); // Switch off I2C , optional may effect other programs & devices
	bcm2835_close(); // Close the library
	printf("OLED End\r\n");
}

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
	
	// Turn on I2C bus.
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

void myLoop() {

		printf("OLED Frame rate per second test , ends at 1000\r\n");
		myOLED.setTextColor(WHITE);
		myOLED.setTextSize(1);
		myOLED.buffer = (uint8_t*) &screenBuffer;  
		if(myOLED.buffer == nullptr)
		{
			printf("Error 1203 :: Problem assigning buffer pointer\r\n");
			exit(-1);
		}
		while (count < 1000)
		{
			static long framerate = 0;
			display_buffer(framerate, count);
			framerate++;
			count++;
		}

}

void display_buffer(long currentFramerate, int count)
{
	// Values to count frame rate per second
	static long lastFramerate = 0;
	static uint16_t fps;
	uint64_t currentCounter = counter();
	if(currentCounter - previousCounter >= 1000000000)
	{
		//(Rolls over every 1 second)
		fps = currentFramerate - lastFramerate;
		lastFramerate = currentFramerate ;
		previousCounter = currentCounter;
		colour = !colour;
	}
	
	myOLED.OLEDclearBuffer();
	
	myOLED.setCursor(0, 0);
	myOLED.print("SSD1306");
	myOLED.setCursor(0, 10);
	myOLED.print("G Lyons");
	myOLED.setCursor(0, 20);
	myOLED.print(myOLED.getLibVerNum());
	
	myOLED.setCursor(0, 30);
	myOLED.print(myOLED.getI2Cspeed());
	myOLED.setCursor(0, 40);
	myOLED.print(count);
	myOLED.setCursor(0, 50);
	myOLED.print(fps);
	myOLED.print(" fps");

	
	myOLED.drawFastVLine(64, 0, 63, WHITE);
	myOLED.fillRect(70, 10, 20, 20, colour);
	myOLED.fillCircle(110, 20, 10, !colour);
	myOLED.drawRoundRect(80, 40, 40, 20, 10, WHITE);

	myOLED.OLEDupdate();
}

// This func returns nano-seconds as a 64-bit unsigned number, 
// monotonically increasing, probably since system boot.
// The actual resolution looks like microseconds. returns nanoseconds
static uint64_t counter( void )
{
  struct timespec now;
  clock_gettime( CLOCK_MONOTONIC, &now );
  return  ((uint64_t)now.tv_sec * 1000000000U) + (uint64_t)now.tv_nsec; 
}
