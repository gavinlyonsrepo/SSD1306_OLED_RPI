
// Example file name : main.cpp
// Description: Test file showing "clock demo"
// URL: https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI
// *****************************


#include <bcm2835.h>
#include <time.h>
#include <stdio.h>
#include "SSD1306_OLED.h"
#include "Bitmap_test_data.h" // Test data for bitmaps

#define myOLEDwidth  128
#define myOLEDheight 64
uint8_t fullscreenBuffer[1024];

SSD1306 myOLED(myOLEDwidth ,myOLEDheight) ; // instantiate  an object

// =============== Function prototype ================
int8_t  setup(void);
void myLoop(void);
void DisplayClock(void);
void SplashScreen(void);
void EndTests(void);

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
	myOLED.OLEDbegin(); // initialize the OLED

	return 1;
}

void myLoop()
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
		
		myOLED.setFontNum(1);
		myOLED.setTextSize(2);
		myOLED.setCursor(20,17);
		sprintf(displayStr, "%i%i:%i%i:%i%i",timenow->tm_hour / 10,
				timenow->tm_hour % 10, timenow->tm_min / 10,
				timenow->tm_min % 10,timenow->tm_sec / 10,timenow->tm_sec % 10);
		myOLED.print(displayStr);
		
		myOLED.setFontNum(1);
		myOLED.setTextSize(1);
		myOLED.setCursor(5,44);
		sprintf(displayStr, "%i%i/%i%i",timenow->tm_mday / 10,timenow->tm_mday % 10, timenow->tm_mon / 10,timenow->tm_mon % 10);
		myOLED.print(displayStr);
		
		myOLED.setCursor(55,44);
		myOLED.print(count);
		
		myOLED.OLEDBitmap(80, 40, 20, 20,  smallImage, false); 
		myOLED.OLEDBitmap(100, 40, 20, 20,  smallImage, true);
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
	myOLED.OLEDBitmap(0, 0, myOLEDwidth, myOLEDheight, fullscreenBitmap, true);
	myOLED.OLEDupdate();
	bcm2835_delay(5000);
	myOLED.OLEDFillScreen(0x00, 0);
	myOLED.OLEDclearBuffer();
}

