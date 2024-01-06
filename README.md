
![ OLED ](https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI/blob/main/extras/image/device.jpg)

# SSD1306_OLED_RPI

## Table of contents

  * [Overview](#overview)
  * [Installation](#installation)
  * [Test](#test)
  * [Hardware](#hardware)
  * [Software](#software)
  	* [API](#api)
	* [I2C](#i2c)
	* [Fonts](#fonts)
	* [Bitmaps](#bitmaps)
  * [Output](#output)
  * [Notes](#notes)


## Overview

* Name : SSD1306_OLED_RPI
* Description :

0. Library to support the I2C 128X64 OLED Display Module
   driven by the SSD1306 controller for the Raspberry PI.
1. Dynamic install-able system level Raspberry Pi C++ library.
2. Inverse color, rotate, sleep, scroll and contrast control.
3. Default font is Extended ASCII, scalable font.
4. 10 fonts included.
5. Graphics class included.
6. Bitmaps supported.
7. Hardware I2C using bcm2835 library
8. Also tested on 128X32 display size. Should work for 96X16 display size.
9. Dependency: bcm2835 Library

* Author: Gavin Lyons

* Development toolchain.
	1. Raspberry PI 3 model b, 
	2. C++ complier g++ (Raspbian 8.3.0-6)
	3. Raspbian 10 buster OS, 32 bit.
	4. bcm2835 Library 1.73 (Dependency)


## Installation


1. Install the dependency bcm2835 Library if not installed (at time of writing latest version is 1.73.)
	* The bcm2835 library is a dependency and provides I2C bus, delays and GPIO control.
	* Install the C libraries of bcm2835, [Installation instructions here](http://www.airspayce.com/mikem/bcm2835/)

2. Download the SSD1306_OLED_RPI library 
	* Open a Terminal in a folder where you want to download,build & test library
	* Run following command to download from github.
    
```sh
curl -sL https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI/archive/1.5.tar.gz | tar xz
```

3. Run "make" to run the makefile in repo base folder to install library, it will be 
    installed to usr/lib and usr/include
    
```sh
cd SSD1306_OLED_RPI-1.5
make
sudo make install
```

## Test

1. Next step is to test OLED and installed library with an example.
Wire up your OLED. Next enter the examples folder and run the makefile in THAT folder, 
This makefile builds the examples file using the just installed library.
and creates a test exe file in "bin". 
The default example file is "hello world", user should see hello world on the OLED
by end of these steps.

```sh
cd examples/
make
make run
```

2. There are 6 examples files to try out. 
To decide which one the makefile builds simply edit "SRC" variable at top of the makefile in examples folder.
in the "User SRC directory Option Section". Pick an example "SRC" directory path and ONE ONLY.
Comment out the rest and repeat: make and make run.

| Filepath | File Function | Screen Size |
| ---- | ---- | ---- | 
| src/HELLO_WORLD | Basic use case | 128x64 |
| src/BITMAP  | Shows use of bitmaps | 128x64 |
| src/CLOCK_DEMO | A basic clock Demo | 128x64 |
| src/OLED_FUNCTIONS |Test functions like scroll, rotate etc | 128x64 |
| src/SPEED_TEST | Frame rate per second test | 128x64 |
| src/TEXT_GRAPHICS |Tests Text , fonts and graphics  | 128x64 |

## Hardware

Manufacturers diagram showing connections.

![ wiring ](https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI/blob/main/extras/image/wiring.jpg)

## Software

### API

The API (application programming interface) documentation is at link hosted on github pages and generated by Doxygen software.
Lots of information on the software.

[ API URL Link](https://gavinlyonsrepo.github.io/misc/software_docs/SSD1306_OLED_RPI/index.html) 

### I2C

Hardware I2C.

1. I2C Address is set by default to 0x3C(your module could be different, 
	user can change argument passed into "OLEDbegin" method).

2. I2C Clock rate can be a passed into in the "OLEDbegin" method as a argument, five possible values : 
If you send 0 (the default) It sets it to 100KHz and uses bcm2835_i2c_set_baudrate to do so.
Alternatively you can pass 1 of 4 BCM2835_I2C_CLOCK_DIVIDER values 2500, 626 150 or 148.
See image below.

3. In the event of an error writing a byte, debug info with error code will be written to console. 
	This error code is the bcm2835I2CReasonCodes enum. Debug flag must be set to true to see this output.
	See image below for  bcm2835I2CReasonCodes. 
	
![ bcm ](https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI/blob/main/extras/image/bcm.jpg)

For more info on bcm2835I2CClockDivider & bcm2835I2CReasonCodes see [bcm2835 doc's for details](http://www.airspayce.com/mikem/bcm2835/group__constants.html)

### Fonts

Font data table: 

| num | enum name | Char size XbyY | ASCII range | Size bytes | Scale-able |
| ------ | ------ | ------ | ------ |  ------ | ----- |
| 1 | $_Default | 5x8 |0-0xFF, Full Extended|1275 |Y|
| 2 | $_Thick   | 7x8 |0x20-0x5A, no lowercase letters |406|Y|
| 3 | $_SevenSeg  | 4x8 |0x20-0x7A |360|Y|
| 4 | $_Wide | 8x8 |0x20-0x5A, no lowercase letters|464|Y|
| 5 | $_Tiny | 3x8 |0x20-0x7E |285|Y|
| 6 | $_Homespun  | 7x8 |0x20-0x7E |658|Y|
| 7 | $_Bignum | 16x32 |0x2D-0x3A ,0-10 - . / : |896|N|
| 8 | $_Mednum | 16x16 |0x2D-0x3A ,0-10 - . / :|448|N|
| 9 | $_ArialRound| 16x24 | 0x20-0x7E |4608|N|
| 10 | $_ArialBold | 16x16 |0x20-0x7E |3072|N|

1. $ = OLEDFontType
2. A print class is available to print out many data types.
3. Fonts 1-6 are byte high(at text size 1) scale-able fonts, columns of padding added by SW.
4. Font 7-8 are large numerical fonts and cannot be scaled(just one size). 
5. Fonts 9-10 large Alphanumeric fonts and cannot be scaled(just one size) 

Font Methods: 

| Font num | Method | Notes |
| ------ | ------ | ------ |
| 1-6 | drawChar| draws single  character |
| 1-6 | drawText | draws character array |
| 7-10 | drawCharBigFont | draws single  character |
| 7-10 | drawTextBigFont | draws character array |
| 1-10 | print | Polymorphic print class which will print out most data types |

### Bitmaps

Two different bitmaps methods can be used.

| num | Method name | data addressing | Notes | 
| ------ | ------ | ------ | ------ |   
| 1 | OLEDBitmap() |horizontal| Draws bitmaps to the buffer | 
| 2 | OLEDBuffer() |vertical | Write a full screen bitmap direct to screen, used internally| 

Bitmaps can be turned to data [here at link]( https://javl.github.io/image2cpp/) 
See example file "BITMAP" for more details.

## Output

Output of the example file "CLOCK_DEMO".

![ op ](https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI/blob/main/extras/image/output.jpg)

## Notes

1. To test on a different size of display edit the myOLEDwidth & myOLEDheight
variables in examples files.

| Display size | Supported | Tested | 
| ------ | ------ | ------ |
| 128x64 | Yes | Yes |
| 128x32 | Yes | Yes |
| ???x16 | Yes | NO |



    
