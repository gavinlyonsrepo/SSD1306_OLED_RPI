
![ OLED ](https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI/blob/main/extras/image/device.jpg)

Table of contents
---------------------------

  * [Overview](#overview)
  * [Installation](#installation)
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
4. 5 other fonts included.
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
curl -sL https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI/archive/1.2.tar.gz | tar xz
```

4. Run "make" to run the makefile in repo base folder to install library, it will be 
    installed to usr/lib and usr/include
    
```sh
cd SSD1306_OLED_RPI-1.2
sudo make
```

5. Next step is to test OLED and installed library with an example.
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

6. There are seven examples files to try out. 
To decide which one the makefile builds simply edit "SRC" variable at top of the makefile in examples folder.
in the "User SRC directory Option Section". Pick an example "SRC" directory path and ONE ONLY.
Comment out the rest and repeat: make and run bin/test.
Six of the examples are for 128x64 (screen size) OLED , the seventh: named HELLO_WORLD_128_32 is for a 128X32 OLED.


Hardware
----------------------------

Connections as per manufacturers diagram.

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

There are Six fonts.
A print class is available to print out most passed data types.
The fonts 1-4 are byte high(at text size 1) scale-able fonts, columns of padding added by SW.
Font 5-6 are large numerical fonts and cannot be scaled(just one size).  
It is possible to use ':' and '.' symbol with these fonts, see examples.

Six fonts available : 

| Font num | Font name | Font size xbyy |  Note |
| ------ | ------ | ------ | ------ |  
| 1 | Default | 5x8 | Full Extended ASCII 0x00 - 0xFF |
| 2 | Thick   | 7x8 | ASCII  0x20 - 0x5A  ,no lowercase letters |
| 3 | Seven segment | 4x8 | ASCII  0x20 - 0x7A |
| 4 | Wide | 8x8 | ASCII 0x20 - 0x5A , no lowercase letters |
| 5 | Big Nums | 16x32 | ASCII 0x30-0x3A , Numbers + : only |
| 6 | med Nums | 16x16 | ASCII 0x30-0x3A , Numbers + : only |

*bitmaps*

Bitmaps can be turned to data [here at link]( https://javl.github.io/image2cpp/) use horizontal addressing draw mode.
Use OLEDBitmap to draw bitmaps to buffer.
You can also write a full screen bitmap direct to screen using OLEDBuffer method, this will use vertical addressing.


Output
--------------------------------

Output of example file "CLOCK_DEMO"

![ op ](https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI/blob/main/extras/image/output.jpg)
