
// Example file name : main.cpp
// Description:
// Test file for SSD1306_OLED library, showing use of mulitple buffers.  
// In this case: two, divided horizontally.
// The user can also divide vertically. and create as many buffers as they want.
// URL: https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI
// *****************************
// NOTES :
// (1) In the <SSD1306_OLED.h> USER BUFFER OPTION SECTION, at top of file
// option MULTI_BUFFER must be selected
// and only this option. It is on by default.
// (2) measured frame rate 279 fps
// ******************************
// 

#include <bcm2835.h>
#include "SSD1306_OLED.h"
#include <time.h>
#include <stdio.h>

#define myOLEDwidth  128
#define myOLEDheight 64

SSD1306 myOLED(myOLEDwidth ,myOLEDheight) ; // instantiate  an object

// vars for the test
uint16_t count  = 0;
bool colour = 1;
uint64_t  previousCounter =0;

// =============== Function prototype ================
uint8_t  setup(void);
void myLoop(void);
void display_buffer(long , int );
void EndTests(void);
static uint64_t counter( void );

// ======================= Main ===================
int main(int argc, char **argv)
{

	if (!setup())
	{
		return -1;
	}
	myLoop();
	EndTests();
	return 0;
}
// ======================= End of main  ===================

void EndTests()
{
	myOLED.OLEDPowerDown(); //Switch off display
	bcm2835_close(); // Close the library
	printf("OLED End\r\n");
}

uint8_t setup()
{
	if(!bcm2835_init())
	{
		printf("Error 1201 Cannot init bcm2835 library\n");
		return -1;
	}
	bcm2835_delay(500);
	printf("OLED Begin\r\n");
	myOLED.OLEDbegin(); // initialize the OLED
	myOLED.OLEDFillScreen(0x01, 0); //splash screen bars
	bcm2835_delay(2500);
	myOLED.setTextColor(WHITE);
	myOLED.setTextSize(1);
	return 1;
}

void myLoop() {
	
	uint8_t  screenBuffer[myOLEDwidth * (myOLEDheight / 8) ]; 
	myOLED.buffer = (uint8_t*) &screenBuffer;  
	while (count < 1000)
	{
		static long framerate = 0;
		display_buffer(framerate, count);
		framerate++;
		count++;
	}

}


// Function to display left hand side buffer
void display_buffer(long currentFramerate, int count)
{
	myOLED.OLEDclearBuffer();
	myOLED.setCursor(0, 0);
	myOLED.print("SSD1306");

	myOLED.setCursor(0, 20);
	myOLED.print("G Lyons");

	myOLED.setCursor(0, 30);
	myOLED.print(count);
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

	myOLED.setCursor(0, 40);
	myOLED.print(fps);
	myOLED.print(" fps");
	myOLED.setCursor(0, 50);
	myOLED.print("V 1.0.0");
	myOLED.drawFastVLine(64, 0, 63, WHITE);

	myOLED.fillRect(70, 10, 20, 20, colour);
	myOLED.fillCircle(110, 20, 10, !colour);
	myOLED.drawRoundRect(80, 40, 40, 20, 10, WHITE);

	myOLED.OLEDupdate();
}

//This returns nano-seconds as a 64-bit unsigned number, monotonically increasing, 
//probably since system boot.
//The actual resolution looks like microseconds. returns nanoseconds
static uint64_t counter( void )
{
  struct timespec now;
  clock_gettime( CLOCK_MONOTONIC, &now );
  return  ((uint64_t)now.tv_sec * 1000000000U) + (uint64_t)now.tv_nsec; 
}
