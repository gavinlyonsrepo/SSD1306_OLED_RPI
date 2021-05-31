
![ OLED ](https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI/blob/main/extras/image/device.jpg)

Table of contents
---------------------------

  * [Overview](#overview)
  * [Usage](#usage)
  * [Hardware](#hardware)
  * [Features](#features)


Overview
--------------------
* Name : SSD1306_OLED_RPI
* Description :

0. Library to support the I2C 128X64 OLED Display Module
   driven by the SSD1306 controller for the Raspberry PI.
1. Raspberry Pi C++ library.
2. Inverse color, rotate, sleep, scroll and contrast control.
3. Default font is Extended ASCII, scalable font.
4. 4 other fonts included.
5. Graphics class included.
6. Bitmaps supported.
7. Hardware I2C using bcm2835 library
8. Also tested on 128X32 display size. Should work for 96X16 display size.
9. Dependency: bcm2835 Library

* Author: Gavin Lyons
* Developed on 
	1. Raspberry PI 3 model b, 
	2. C++ complier g++ (Raspbian 6.3.0-18)
	3. Raspbian 9.13 stretch OS
	4. bcm2835 Library 1.68 


Usage
------------------------------

1. Make sure I2C bus is enabled on your raspberry PI

2. Install the bcm2835 Library (at time of writing latest version is 1.68.)
	* The bcm2835 libray is a dependency and provides I2C bus, delays and GPIO control.
	* Install the C libraries of bcm2835, [Installation instructions here](http://www.airspayce.com/mikem/bcm2835/)

3. Download the SSD1306_OLED_RPI library 
	* Open a Terminal in a folder where you want to create your project.
	* Run following commands
```sh
curl -sL https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI/archive/1.0.tar.gz | tar xz
cd SSD1306_OLED_RPI_1.0
```

4. Build the project, by running the makefile included.
	* The "hello world" example, main.cpp is in the "src" folder ready to go. 
	* Run make to run the makefile and build the project.
	* The makefile does NOT install to system at present, it  builds the code in that folder.
```sh
make
```

5. Run the program to display on OLED.
	* The makefile creates a executable binary test file at ./bin/test
	* This program should display hello world on your OLED.
	* Be sure to use "sudo" as the bcm2835 demands root permissions [ see here for more details](http://www.airspayce.com/mikem/bcm2835/) 

```sh
sudo ./bin/test
```

6. Try out other examples  if you wish!
	* There are 6 different main.cpp in the examples folder, Copy the main.cpp you want to see into  "src" folder
	* Examples: Hello world , Speed test , Text and graphics test , bitmap test , Clock Demo, OLED functions.  

7. Copy the library code into your project folder directory however you wish to organise it 
	* The header files are in the include folder in my repo.
	* And the soucre files are in src in my repo.
	* If you are not using included makefile to build be sure to include -lbcm2835 flag.


Hardware
----------------------------

Connections as per manufacturers diagram, I2C bus pull-up resistors are on module.
If 3.3V regulator on back of module can be powered from 5V PSU.

![ wiring ](https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI/blob/main/extras/image/wiring.jpg)

Features
-------------------------

*I2C*

Hardware I2C.
Settings are in the "OLED_I2C_ON" method.

1. Address is set to 0x3C(your module could be different).
2. Clock rate is to BCM2835_I2C_CLOCK_DIVIDER_626   
	This can be increased if necessary to BCM2835_I2C_CLOCK_DIVIDER_148
	for more faster bus. See [bcm2835 for details](http://www.airspayce.com/mikem/bcm2835/) 


*fonts*

There are five fonts.
A print class is available to print out most passed data types.
The fonts 1-4 are byte high(at text size 1) scale-able fonts, columns of padding added by SW.
Font 5 is special font large font but it is numbers only and cannot
use the print class or be scaled(just one size).  

Five fonts available : 

| Font num | Font name | Font size xbyy |  Note |
| ------ | ------ | ------ | ------ |  
| 1 | Default | 5x8 | Full Extended ASCII 0 - 0xFF |
| 2 | Thick   | 7x8 | no lowercase letters , ASCII  0x20 - 0x5A |
| 3 | Seven segment | 4x8 | ASCII  0x20 - 0x7A |
| 4 | Wide | 8x8 | no lowercase letters, ASCII 0x20 - 0x5A |
| 5 | Big Nums | 16x32 | ASCII 0x2E-0x3A ,Numbers + : . only |

*bitmaps*

Bitmaps can be turned to data [here at link]( https://javl.github.io/image2cpp/) use horizontal addressing draw mode.
Use OLEDBitmap to draw bitmaps to buffer.
You can also write a full screen bitmap direct to screen using OLEDBuffer method, this will use vertical addressing.
