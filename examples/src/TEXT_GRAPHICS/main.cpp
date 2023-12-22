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
		-# Test 705 print ASCII font 0-127
		-# Test 706 print ASCII font 128-255
		-# Test 707 thick font 2 (NO LOWERCASE)
		-# Test 708 seven seg font 3
		-# Test 709 wide font 4 (NO LOWERCASE)
		-# Test 710 tiny font 5
		-# Test 711 homespun font 6
		-# Test 712 bigNums font 7(numeric font  0-10 : . / -)
		-# Test 713 medNums font 8 (numeric font 0-10 + : . / -)
		-# Test 714 Arial round font 9
		-# Test 715 Arial bold font 10
		-# Test 716 various print method tests
		-# Test 717 drawtext method text screen wrap
		-# Test 901 Graphics test
*/

#include <bcm2835.h>
#include <time.h>
#include <stdio.h>
#include "SSD1306_OLED.hpp"

#define myOLEDwidth  128
#define myOLEDheight 64
SSD1306 myOLED(myOLEDwidth ,myOLEDheight) ; // instantiate  an object

// Test timing delays 
#define DisplayDelay1 4000
#define DisplayDelay2 0


// =============== Function prototype ================
bool SetupTest(void);
void myTests(void);
void EndTests(void);
void TestReset(void);

void DisplayTextTests1(void);
void DisplayTextTests2(void);
void DisplayTextTests3(void);
void DisplayGraphics(void);

// ======================= Main ===================
int main(int argc, char **argv)
{
	SetupTest();
	myTests();
	EndTests();
	return 0;
}
// ======================= End of main  ===================


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

	// Define a full screen buffer
	uint8_t  screenBuffer[(myOLEDwidth * (myOLEDheight / 8)) + 1];
	myOLED.buffer = (uint8_t*) &screenBuffer;  
	if(myOLED.buffer == nullptr) // check if pointer is still = null
	{
		printf("Error 1203 :: Problem assigning buffer pointer\r\n");
		exit(-1);
	}
	
	DisplayTextTests1();
	DisplayTextTests2();
	DisplayTextTests3();
	DisplayGraphics();
}

void TestReset(void){
	myOLED.OLEDupdate();
	bcm2835_delay(DisplayDelay1);
	myOLED.OLEDclearBuffer();
}

void DisplayTextTests1()
{

	myOLED.setTextWrap(true);
	myOLED.setFontNum(OLEDFontType_Default);
	
	myOLED.OLEDclearBuffer(); // Clear the buffer
	// Test 701
	printf("OLED Test 701 Default Font size 3 float\r\n");
	myOLED.setTextColor(WHITE);
	myOLED.setTextSize(3);
	myOLED.setCursor(0, 0);
	float PI = 3.14;
	myOLED.print(PI);

	// Test 702
	printf("OLED Test 702 Default font size 2 integer\r\n");
	myOLED.setTextSize(2);
	myOLED.setCursor(0, 30);
	int count = 123;
	myOLED.print(count);

	// Test 703
	printf("OLED Test 703 Default font, size 1 string inverted\r\n");
	myOLED.setTextSize(1);
	myOLED.setTextColor(BLACK, WHITE);
	myOLED.setCursor(0, 50);
	myOLED.print("Hello World");

	// Test 704
	printf("OLED Test 704 Default font ,size 4, single character\r\n");
	myOLED.drawChar(95, 15 , 'H', WHITE, BLACK, 6);

	TestReset();

	// Test 705
	printf("OLED Test 705 Default font print ASCII table 0-127 \r\n");
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
	
	// Test 706
	printf("OLED Test 706 Default font  print ASCII table 128-255 \r\n");
	for (uint8_t i = 128; i < 255; i++)
	{
		if (x > 120)
		{
			x = 0;
			y += 9;
		}
		myOLED.drawChar(x, y , i, WHITE, BLACK, 1);
		x += 7;
		bcm2835_delay(DisplayDelay2);
	}

	TestReset();
	
	// Test 707
	printf("OLED Test 707 thick font 2 (NO LOWERCASE) \r\n");
	myOLED.setFontNum(OLEDFontType_Thick);
	myOLED.setTextSize(1);
	myOLED.setCursor(0, 0);
	myOLED.print("THE THICK FONT");
	myOLED.setCursor(0, 9);
	myOLED.print("NO LOWERCASE");
	myOLED.drawChar(70, 20 , 'H', WHITE, BLACK, 4);
	myOLED.setCursor(0, 45);
	myOLED.setTextSize(2);
	myOLED.print(1234);
	TestReset();
	
	// Test 708
	printf("OLED Test 708 seven seg font 3 \r\n");
	myOLED.setFontNum(OLEDFontType_SevenSeg);
	myOLED.setTextSize(1);
	myOLED.setCursor(0, 0);
	myOLED.print("SEVEN SEG Font");
	myOLED.setCursor(0, 9);
	myOLED.print("123456789012345678012345");
	myOLED.setCursor(0, 30);
	myOLED.setTextSize(5);
	myOLED.print(-14.8);
	TestReset();
	
	// Test 709
	printf("OLED Test 709 wide font (NO LOWERCASE) \r\n");
	myOLED.setFontNum(OLEDFontType_Wide);
	myOLED.setTextSize(1);
	myOLED.setCursor(0, 0);
	myOLED.print("WIDE FONT");
	myOLED.setCursor(0, 9);
	myOLED.print("NO LOWERCASE 4");
	myOLED.setCursor(0, 30);
	myOLED.setTextSize(2);
	myOLED.print(13.57);
	TestReset();
	
	// Test 710
	printf("OLED Test 710 tiny font \r\n");
	myOLED.setFontNum(OLEDFontType_Tiny);
	myOLED.setTextSize(1);
	myOLED.setCursor(0, 0);
	myOLED.print("tiny Font:");
	myOLED.setCursor(0, 15);
	myOLED.print("123456 tiny");
	myOLED.setCursor(0, 35);
	myOLED.setTextSize(2);
	myOLED.print("99:52");
	TestReset();
	
	// Test 711
	printf("OLED Test 711 homespun font \r\n");
	myOLED.setFontNum(OLEDFontType_Homespun);
	myOLED.setTextSize(1);
	myOLED.setCursor(0, 0);
	myOLED.print("Homespun Font:");
	myOLED.setCursor(0, 15);
	myOLED.print("123456 home");
	myOLED.setCursor(0, 35);
	myOLED.setTextSize(2);
	myOLED.print(19.6657, 3); // print 19.666
	TestReset();
	
}

void DisplayTextTests2()
{
	// Test 712
	printf("OLED Test 712 bigNums font 7(NUMBERS / : . - ONLY)\r\n");
	
	myOLED.setFontNum(OLEDFontType_Bignum);
	char myString[9] = {'1','9',':','2','2',':','3','8'};
	myOLED.drawCharBigFont(0, 0, '8', BLACK, WHITE); // single character inverted
	myOLED.drawTextBigFont(0, 32, myString , WHITE, BLACK); 
	
	TestReset(); 
	
	myOLED.setTextColor(WHITE, BLACK); // normal
	myOLED.setCursor(0, 0);
	myOLED.print(-87.39);
	myOLED.setTextColor(BLACK, WHITE); //invert
	myOLED.setCursor(0, 32);
	myOLED.print(-99.67);
	
	TestReset();
	
	// Test 713
	
	printf("OLED Test 713 medNums font 8(NUMBERS : . / - ONLY)\r\n");
	
	myOLED.setFontNum(OLEDFontType_Mednum);
	char myTest[] = "1234567812::5678";
	myOLED.drawCharBigFont(0, 40, '9', BLACK, WHITE); // single character inverted
	myOLED.drawTextBigFont(0, 0, myTest, WHITE, BLACK);
	
	TestReset();
	
	myOLED.setTextColor(BLACK, WHITE); //invert
	myOLED.setCursor(5, 10);
	myOLED.print(-35.96);
	myOLED.setTextColor(WHITE, BLACK); // normal
	myOLED.setCursor(5, 30);
	myOLED.print(-19.98);
	
	TestReset();
	
	// Test 714 Arial round
	printf("OLED Test 714 Arial round font \r\n");
	myOLED.setFontNum(OLEDFontType_ArialRound);
	myOLED.setCursor(0, 0);
	myOLED.print("Arial");
	char myTest14[] = "123";
	myOLED.drawTextBigFont(0,25, myTest14, BLACK, WHITE);
	
	TestReset();
	
	myOLED.setCursor(0, 0);
	myOLED.print(-27.31);
	myOLED.setTextColor(BLACK, WHITE); //invert
	myOLED.setCursor(0, 24);
	myOLED.print(1234.0);
	
	TestReset();
	
	// Test 715 Arial bold
	printf("OLED Test 715 Arial bold font  \r\n");
	myOLED.setFontNum(OLEDFontType_ArialBold);
	myOLED.setCursor(0, 0);
	myOLED.print("Arial B");
	myOLED.drawTextBigFont(5, 25, myTest14, BLACK, WHITE);
	
	TestReset();
	
	myOLED.setTextColor(WHITE, BLACK); // normal
	myOLED.setCursor(0, 0);
	myOLED.print(346.91);
	myOLED.setTextColor(BLACK, WHITE); // invert
	myOLED.setCursor(0, 40);
	myOLED.print(-19);
	myOLED.setTextColor(WHITE, BLACK); // normal
	
	TestReset();
}

void DisplayTextTests3()
{

	// Test 716-a 
	printf("OLED Test 716-A Base number systems using print \r\n");
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
	
	// Test 716-B string method
	printf("OLED Test 716-B string object method using print \r\n");
	std::string timeInfo = "12:45";
	myOLED.setCursor(5, 0);
	myOLED.println(timeInfo);
	myOLED.print(timeInfo);
	TestReset();
	
	// Test 716-C
	printf("OLED Test 716-C print overlap  + invert \r\n");
	myOLED.setFontNum(OLEDFontType_Homespun);
	myOLED.setCursor(0, 0);
	myOLED.print("1234567890abcdefghij");
	myOLED.setCursor(0, 32);
	myOLED.setTextColor(BLACK, WHITE); // invert
	myOLED.print("inverted"); 
	TestReset();
	
	
	// Test 717
	printf("OLED Test 717 drawtext method overlap \r\n");
	char myString[9] = {'1','9',':','2','2',':','3','8'};
	char myTest[] = "1234567812::5678";
	myOLED.setTextColor(WHITE, BLACK); // normal
	myOLED.setFontNum(OLEDFontType_Tiny);
	myOLED.drawText(0,0, myString, WHITE, BLACK,1);
	myOLED.setFontNum(OLEDFontType_Wide);
	myOLED.drawText(0,32, myTest, WHITE, BLACK,2);
	TestReset(); 
	
} 

// Function to display Graphics.
void  DisplayGraphics()
{
	//Q1 ||  Q2
	//---------
	//Q3 ||  Q4
	printf("OLED Test 901 graphics test \r\n");
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
