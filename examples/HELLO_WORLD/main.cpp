
// Example file name : main.cpp
// Description:
// Test file for SSD1306_OLED library, showing  hello world
// URL: https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI
// *****************************


#include <bcm2835.h>
#include "SSD1306_OLED.h"
#include <time.h>
#include <stdio.h>

#define myOLEDwidth  128
#define myOLEDheight 64

SSD1306 myOLED(myOLEDwidth ,myOLEDheight) ; // instantiate  an object 

// =============== Function prototype ================
void SetupTest(void);
void TestLoop(void);
void EndTest(void);

// ======================= Main ===================
int main(int argc, char **argv) 
{
	if(!bcm2835_init())
	{
		printf("Error 1201: init bcm2835 library\r\n");
		return -1;
	}
	
	SetupTest();
	TestLoop();
	EndTest();
	
	return 0;
}
// ======================= End of main  ===================

// ===================== Function Space =====================
void SetupTest() 
{
	bcm2835_delay(500);
	printf("OLED Begin\r\n");
	myOLED.OLEDbegin(); // initialize the OLED
	myOLED.OLEDFillScreen(0xF0, 0); // splash screen bars
	bcm2835_delay(1500);
}

void EndTest()
{
	myOLED.OLEDPowerDown(); //Switch off display
	bcm2835_close(); // Close the library
	printf("OLED End\r\n");
}

void TestLoop() 
{

	// Define a buffer to cover whole screen 
	uint8_t  screenBuffer[myOLEDwidth * (myOLEDheight/8)+1]; 
 	myOLED.buffer = (uint8_t*) &screenBuffer;  // set that to library buffer pointer

	myOLED.OLEDclearBuffer(); // Clear active buffer 
	myOLED.setTextColor(WHITE);
	myOLED.setCursor(0, 0);
	myOLED.print("Hello world");
	myOLED.OLEDupdate();  //write to active buffer
	delay(5000);

}

// ============== EOF =========
