
![ OLED ](https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI/blob/main/extras/image/device.jpg)

Table of contents
---------------------------

  * [Overview](#overview)
  * [Installation](#installation)
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

* Author: Gavin Lyons
* Developed on 
	1. Raspberry PI 3 model b, 
	2. C++ complier g++ (Raspbian 6.3.0-18)
	3. Raspbian 9.13 stretch OS

* Based on my [PIC OLED library](https://github.com/gavinlyonsrepo/pic_16F18346_projects) and my [RPI CH1115 SPI OLED library](https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115_RPI)


 Installation
------------------------------

Install the C libraries of bcm2835, see: http://www.airspayce.com/mikem/bcm2835/
The bcm2835 is a dependency and provides I2C bus, delays and GPIO control.
There are 7 different main.cpp in the examples folder copy the one to run into src folder
"Hello world" is in src by default. Make sure to run test file with sudo

To Install and run "hello world" execute following commands:

```sh
curl -sL https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI/archive/1.0.tar.gz | tar xz
cd SSD1306_OLED_RPI_1.0
make
sudo ./bin/test
```

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
