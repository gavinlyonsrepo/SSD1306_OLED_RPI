/*!
	@file SSD1306_OLED_RPI/examples/src/TEXT_GRAPHICS/main.cpp
	@author Gavin Lyons
	@brief Test file for SSD1306_OLED library, showing use of TEXT mode & graphics.
	
	Project Name: SSD1306_OLED_RPI
	
	@test
		-# Test 701 Font size 3 float
		-# Test 702 font size 2 integer
		-# Test 703 font size 1 string inverted
		-# Test 704 draw a single character font size 4
		-# Test 705 print ASCII  font 0-127
		-# Test 706 print ASCII font 128-255
		-# Test 707 thick font 2 (NO LOWERCASE)
		-# Test 708 seven seg font 3
		-# Test 709 wide font (NO LOWERCASE)
		-# Test 710 tiny font
		-# Test 711 homespun font
		-# Test 712 bigNums font 7(NUMS ONLY + : )
		-# Test 713 medNums font 8 (NUMS ONLY + : )
		-# Test 714 test print method 
		-# Test 715 Drawtext
*/

#include <bcm2835.h>
#include <time.h>
#include <stdio.h>

#include "SSD1306_OLED.hpp"

#define myOLEDwidth  128
#define myOLEDheight 64

#define DisplayDelay1 4000
#define DisplayDelay2 0

const uint16_t I2C_Speed = 626; //  bcm2835I2CClockDivider 
const uint8_t I2C_Address = 0x3C;
SSD1306 myOLED(myOLEDwidth ,myOLEDheight) ; // instantiate  an object

// =============== Function prototype ================
void SetupTest(void);
void TestLoop(void);
void DisplayText( );
void DisplayGraphics( );
void EndTest(void);
void TestReset(void);

// ======================= Main ===================
int main(int argc, char **argv)
{
	if(!bcm2835_init())
	{
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
	myOLED.OLEDbegin(I2C_Speed, I2C_Address); // initialize the OLED
	myOLED.OLEDFillScreen(0x8F, 0); //splash screen bars
	bcm2835_delay(1000);
}

void EndTest()
{
	myOLED.OLEDPowerDown(); //Switch off display
	bcm2835_close(); // Close the library
	printf("OLED End\r\n");
}

void TestLoop()
{

	// Define a full screen buffer
	uint8_t  screenBuffer[(myOLEDwidth * (myOLEDheight / 8)) + 1];
	myOLED.buffer = (uint8_t*) &screenBuffer;  
	

	DisplayText();
	DisplayGraphics();
}

void TestReset(void){
	myOLED.OLEDupdate();
	bcm2835_delay(DisplayDelay1);
	myOLED.OLEDclearBuffer();
}


void DisplayText()
{

	myOLED.setTextWrap(true);
	myOLED.setFontNum(OLEDFontType_Default);
	
	myOLED.OLEDclearBuffer(); // Clear the buffer
	// Test 1
	myOLED.setTextColor(WHITE);
	myOLED.setTextSize(3);
	myOLED.setCursor(0, 0);
	float PI =3.14;
	myOLED.print(PI);

	// Test 2
	myOLED.setTextSize(2);
	myOLED.setCursor(0, 30);
	int count = 123;
	myOLED.print(count);

	// Test 3
	myOLED.setTextSize(1);
	myOLED.setTextColor(BLACK, WHITE);
	myOLED.setCursor(0, 50);
	myOLED.print("Hello World");

	// Test 4
	myOLED.drawChar(95, 15 , 'H', WHITE, BLACK, 6);

	TestReset();

	// Test 5
	myOLED.setCursor(0, 0);
	myOLED.setTextColor(WHITE);
	myOLED.setTextSize(1);
	myOLED.print("ASCII font ");
	myOLED.setCursor(0, 15);
	char offset = 0;

	// Print first 127 chars of font
	for (char i = offset; i < 126; i++)
	{
		if (i == '\n' || i == '\r') continue;
		myOLED.print(i);
		bcm2835_delay(DisplayDelay2);
	}
	TestReset();

	myOLED.setCursor(0, 0);
	myOLED.setTextColor(WHITE);
	myOLED.setTextSize(1);
	myOLED.print("ASCII font 128-255");

	uint8_t x = 0;
	uint8_t y = 15;
	myOLED.setCursor(x, y);

	for (uint8_t i = 128; i < 255; i++)
	{
		if (x > 180)
		{
			x = 0;
			y += 9;
		}
		myOLED.drawChar(x, y , i, WHITE, BLACK, 1);
		x += 7;
		bcm2835_delay(DisplayDelay2);
	}

	TestReset();
	
	// Test 7
	myOLED.setFontNum(OLEDFontType_Thick);
	myOLED.setTextSize(1);
	myOLED.setCursor(0, 0);
	myOLED.print("THE THICK FONT");
	myOLED.setCursor(0, 9);
	myOLED.print("1234567890123456");
	myOLED.drawChar(70, 20 , 'H', WHITE, BLACK, 4);
	myOLED.setCursor(0, 45);
	myOLED.setTextSize(2);
	myOLED.print("TEST");
	TestReset();
	
	// Test 8
	myOLED.setFontNum(OLEDFontType_SevenSeg);
	myOLED.setTextSize(1);
	myOLED.setCursor(0, 0);
	myOLED.print("SEVEN SEG Font");
	myOLED.setCursor(0, 9);
	myOLED.print("123456789012345678012345");
	myOLED.setCursor(0, 30);
	myOLED.setTextSize(5);
	myOLED.print("14:30");
	TestReset();
	
	// Test 9
	myOLED.setFontNum(OLEDFontType_Wide);
	myOLED.setTextSize(1);
	myOLED.setCursor(0, 0);
	myOLED.print("WIDE FONT");
	myOLED.setCursor(0, 9);
	myOLED.print("12345678901234");
	myOLED.setCursor(0, 30);
	myOLED.setTextSize(2);
	myOLED.print("13:57");
	TestReset();
	
	// Test 10
	myOLED.setFontNum(OLEDFontType_Tiny);
	myOLED.setTextSize(1);
	myOLED.setCursor(0, 0);
	myOLED.print("tiny Font:");
	myOLED.setCursor(0, 15);
	myOLED.print("123456 tiny");
	myOLED.setCursor(0, 35);
	myOLED.setTextSize(2);
	myOLED.print("T 11:52");
	TestReset();
	
	// Test 11
	myOLED.setFontNum(OLEDFontType_Homespun);
	myOLED.setTextSize(1);
	myOLED.setCursor(0, 0);
	myOLED.print("Home Font:");
	myOLED.setCursor(0, 15);
	myOLED.print("123456 home");
	myOLED.setCursor(0, 35);
	myOLED.setTextSize(2);
	myOLED.print("T 19:24");
	TestReset();
	
	// Test 12
	myOLED.setFontNum(OLEDFontType_Bignum);
	myOLED.setTextColor(WHITE, BLACK);
	char myString[9] = {'1','9',':','2','2',':','3','8'};
	myOLED.drawCharNumFont(0, 0, '8', BLACK, WHITE); // single character inverted
	myOLED.drawTextNumFont(0, 32, myString , WHITE, BLACK); 
	
	myOLED.OLEDupdate();  // Write to the buffer
	bcm2835_delay(DisplayDelay1);
	myOLED.OLEDclearBuffer();
	
	// Test 13
	myOLED.setFontNum(OLEDFontType_Mednum);
	char myTest[] = "1234567812::5678";
	myOLED.drawCharNumFont(0, 40, '9', BLACK, WHITE); // single character inverted
	myOLED.drawTextNumFont(0, 0, myTest, WHITE, BLACK);
	
	TestReset();
	
	// Test 14 print
	myOLED.setTextColor(WHITE, BLACK);
	
	myOLED.setFontNum(OLEDFontType_Bignum);
	myOLED.setCursor(0, 0);
	myOLED.print(-87.39);
	
	myOLED.setFontNum(OLEDFontType_Mednum);
	myOLED.setCursor(0, 40);
	myOLED.print(3.9);
	myOLED.print(-19);
	
	TestReset();
	
	// Test 14b print
	 myOLED.setFontNum(OLEDFontType_Default);
	myOLED.setCursor(0, 0);
	myOLED.print(47 , DEC);
	myOLED.setCursor(0, 16);
	myOLED.print(47 , HEX); 
	myOLED.setCursor(0, 32);
	myOLED.print(47, BIN);
	myOLED.setCursor(0, 48);
	myOLED.print(47 , OCT);
	TestReset();
	
	// Test 15 drawtext
	myOLED.setFontNum(OLEDFontType_Tiny);
	myOLED.drawText(0,0, myString, WHITE, BLACK,1);
	myOLED.setFontNum(OLEDFontType_Wide);
	myOLED.drawText(0,32, myTest, WHITE, BLACK,2);
	TestReset(); 
	
} // end  DisplayText()

// Function to display Graphics.
void  DisplayGraphics()
{
	//Q1 ||  Q2
	//---------
	//Q3 ||  Q4
	//
	bool colour = 1;
	uint8_t count = 0;
	myOLED.OLEDclearBuffer(); // Clear the buffer
	while (count < 15)
	{
		colour = !colour;

		// Draw the X
		myOLED.drawLine(64,  0, 64, 64, WHITE);
		myOLED.drawFastVLine(62, 0, 64, WHITE);
		myOLED.drawFastHLine(0, 32, 128, WHITE);

		// Q1
		myOLED.fillRect(0, 10, 20, 20, colour);
		myOLED.fillCircle(40, 20, 10, WHITE);

		// Q2
		myOLED.fillTriangle(80, 25, 90, 5, 100, 25, !colour);
		myOLED.drawRect(105, 10, 15, 15, WHITE);
		// Q3
		myOLED.fillRoundRect(0, 40, 40, 20, 10, !colour);
		// Q4
		char i;
		for (i = 0; i < 10; i ++)
		{
			myOLED.drawRect(70 + i, 40 + i, 50 - i * 2, 20 - i * 2, WHITE);
			myOLED.OLEDupdate();
			bcm2835_delay(50);
		}
		myOLED.OLEDclearBuffer();
		count++;
	}
}
