# Changelog

* version 1.0.0 May 2021
	* first release.
* Version 1.1 June 2021
	* packaged library files as a dynamic C++ install-able system level library complete with makefile.
* version 1.2 July 2021
	* Added Large Numerical fonts (7&8) and changed print class functionality so print class works with them.
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
