# Changelog

* version 1.0.0 May 2021
	* first release.
* version 1.3 Jan 2023
	* Added Fonts, tiny and homespun.
	* Added "Drawtext" method
	* Added ability to change I2C bus speed and address in "begin" method
	* Added debug messages to I2C write byte method
	* Large Numerical fonts(7&8) can now display negative sign.
* version 1.4 Sep 2023
	* Some code optimisations.
	* String object support added to print class.
	* Added Doxygen style comments to create automated API.
* version 1.5 Dec 2023
	* Added large alphaNumeric fonts(9-10), Arial bold and Arial round.
	* Increased size of Numerical fonts (7&8) from 11 to 14 characters.
	* Refactored I2C bus control to give user more control and visibility.
	* Changed CCFLAGS in root directory Makefile to allow for Compilation on 64-bit systems. See Pull request number 2 on github
	* Fixed bug in "println" method for String objects.
* version 1.6 Jan 2024
	* Added Fonts 11 and 12
	* Added Error enum OLED_return_codes_e to text and bitmap methods.
	* Added User ability to change I2C error delay and retry attempts. 
* version 1.6.1 Feb 2024
	* minor update, modified the screen boundary check in 'drawPixel' method 
	so 90 and 270 degree screen rotation works fully for entire rotated screen area.
