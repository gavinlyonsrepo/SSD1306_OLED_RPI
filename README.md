
![ OLED ](https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI/blob/main/extras/image/device.jpg)

Table of contents
---------------------------

  * [Overview](#overview)
  * [Installation](#installation)
  * [Test](#test)
  * [Hardware](#hardware)
  * [Features](#features)
  * [Output](#output)


Overview
--------------------
* Name : SSD1306_OLED_RPI
* Description :

0. Library to support the I2C 128X64 OLED Display Module
   driven by the SSD1306 controller for the Raspberry PI.
1. Dynamic install-able system level Raspberry Pi C++ library.
2. Inverse color, rotate, sleep, scroll and contrast control.
3. Default font is Extended ASCII, scalable font.
4. 8 fonts included.
5. Graphics class included.
6. Bitmaps supported.
7. Hardware I2C using bcm2835 library
8. Also tested on 128X32 display size. Should work for 96X16 display size.
9. Dependency: bcm2835 Library

* Author: Gavin Lyons
	1. Raspberry PI 3 model b, 
	2. C++ complier g++ (Raspbian 8.3.0-6)
	3. Raspbian 10 buster  OS
	4. bcm2835 Library 1.68 (Dependency)


Installation
------------------------------

1. Make sure I2C bus is enabled on your raspberry PI

2. Install the dependency bcm2835 Library if not installed (at time of writing latest version is 1.68.)
	* The bcm2835 library is a dependency and provides I2C bus, delays and GPIO control.
	* Install the C libraries of bcm2835, [Installation instructions here](http://www.airspayce.com/mikem/bcm2835/)

3. Download the SSD1306_OLED_RPI library 
	* Open a Terminal in a folder where you want to download,build & test library
	* Run following command to download from github.
    
```sh
curl -sL https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI/archive/1.3.tar.gz | tar xz
```

4. Run "make" to run the makefile in repo base folder to install library, it will be 
    installed to usr/lib and usr/include
    
```sh
cd SSD1306_OLED_RPI-1.3
sudo make
```

Test
------------------------

1. Next step is to test OLED and installed library with an example.
Wire up your OLED. Next enter the examples folder and run the makefile in THAT folder, 
This makefile builds the examples file using the just installed library.
and creates a test exe file in "bin". Be sure to use "sudo" as the bcm2835 requires root permissions by default [ see here for more details on that](http://www.airspayce.com/mikem/bcm2835/) 
The default example file is "hello world",  user should see hello world on the OLED
by end of this step.

```sh
cd examples/
make
sudo bin/test
```

2. There are seven examples files to try out. 
To decide which one the makefile builds simply edit "SRC" variable at top of the makefile in examples folder.
in the "User SRC directory Option Section". Pick an example "SRC" directory path and ONE ONLY.
Comment out the rest and repeat: make and run bin/test.

| Filepath | File Function | Screen Size |
| ---- | ---- | ---- | 
| src/HELLO_WORLD | Basic use case | 128X64 |
| src/BITMAP  | Shows use of bitmaps | 128X64 |
| src/CLOCK_DEMO | A basic clock Demo | 128X64 |
| src/OLED_FUNCTIONS |Test functions like scroll, rotate etc | 128X64 |
| src/SPEED_TEST | Frame rate per second test | 128X64 |
| src/TEXT_GRAPHICS |Tests Text , fonts and graphics  | 128X64 |
| src/HELLO_WORLD_128_32 | Basic use case  | 128X32 |

Hardware
----------------------------

Connections as per manufacturers diagram.

![ wiring ](https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI/blob/main/extras/image/wiring.jpg)

Features
-------------------------

*I2C*

Hardware I2C.

1. I2C Address is set by default to  0x3C(your module could be different, 
	user can change argument passed into "OLEDbegin" method).
2. In the event of an error writing a byte debug info with error code will be written to screen.
	This error code is the bcm2835I2CReasonCodes enum.

3. I2C Clock rate can be a passed into in the "OLEDbegin" method as a argument, five possible values : 

| Value | Method | I2C speed | 
| ---- | ---- | ---- | 
| 0 (default) | bcm2835_i2c_set_baudrate(100000) | 100Khz | 
| 2500 | bcm2835_i2c_setClockDivider(BCM2835_I2C_CLOCK_DIVIDER_2500) | 100Khz | 
| 626 | bcm2835_i2c_setClockDivider(BCM2835_I2C_CLOCK_DIVIDER_626) | 399.4 kHz | 
| 150 | bcm2835_i2c_setClockDivider(BCM2835_I2C_CLOCK_DIVIDER_150) | 1.666 MHz | 
| 148 | bcm2835_i2c_setClockDivider(BCM2835_I2C_CLOCK_DIVIDER_148) | 1.689 MHz | 


For more info on bcm2835I2CClockDivider & bcm2835I2CReasonCodes see [bcm2835 doc's for details](http://www.airspayce.com/mikem/bcm2835/group__constants.html)


*fonts*

There are Eight fonts.
A print class is available to print out most passed data types.
The fonts 1-6 are byte high(at text size 1) scale-able fonts, columns of padding added by SW.
Font 7-8 are large numerical fonts and cannot be scaled(just one size).  
It is possible to use ':',  '.' and '-' symbol's with these fonts, see example file for details

Eight fonts available : 

Font data table: 

| Font num | Font enum name | Font size xbyy |  ASCII range | Size in bytes |
| ------ | ------ | ------ | ------ |  ------ | 
| 1 | OLEDFontType_Default | 5x8 | ASCII 0 - 0xFF, Full Extended  | 1275 |
| 2 | OLEDFontType_Thick   | 7x8 |  ASCII  0x20 - 0x5A, no lowercase letters | 406 | 
| 3 | OLEDFontType_SevenSeg  | 4x8 | ASCII  0x20 - 0x7A | 360 |
| 4 | OLEDFontType_Wide | 8x8 |  ASCII 0x20 - 0x5A, no lowercase letters| 464 |
| 5 | OLEDFontType_Tiny | 3x8 | ASCII  0x20 - 0x7E | 285 |
| 6 | OLEDFontType_Homespun  | 7x8 | ASCII  0x20 - 0x7E |  658 |
| 7 | OLEDFontType_Bignum | 16x32 | ASCII 0x30-0x3A ,Numbers + : only | 704 |
| 8 | OLEDFontType_Mednum | 16x16 | ASCII 0x30-0x3A , Numbers + : only | 352 |

*bitmaps*

Bitmaps can be turned to data [here at link]( https://javl.github.io/image2cpp/) use horizontal addressing draw mode.
Use OLEDBitmap to draw bitmaps to buffer.
You can also write a full screen bitmap direct to screen using OLEDBuffer method, this will use vertical addressing.


Output
--------------------------------

Output of example file "CLOCK_DEMO"

![ op ](https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI/blob/main/extras/image/output.jpg)
