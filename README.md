MSP430 IO Expander Firmware
=============================

Simple set MSP430 firmware converting the MSP430 into an IO expander accessible through I2C on the host.

Currently the only available firmware is the `dio` (Digital IO) firmware. This firmware provides 
8 digital IO ports accessibale through I2C on the master device. Each port could be configured
as input or output. For each input pull-up/downi resistors could be set. It is also possible to 
enable interrupts for inputs. Interrupts could be queried through special register later on. 
 

Project Directory Layout
------------------------

The top-level directory structure of the project looks something like this:

* `Makefile` 		toplevel Make file
* `README.md`		this README
* `setenv.sh`		source to set cross-compile environment (for tests and I2C master sources)
* `dio`				firmware which provides simple digital IO
* `bin`				the resulting firmware
* `test`			some tests to perform againt the firmware


Prerequisites
-------------

To compile all the libraries, firmware variants and test firmwares, the following mandatory tools need 
to be installed on your Linux build-host:

* msp430-gcc for compiling (I use 4.5.3 which is `available on Ubuntu as packet)
* mspdebug for flashing (I use 0.16 which is `available on Ubuntu as packet)
* GNU-make or make (I use GNU make 3.81 which is available also as a packet on Ubuntu) 


Compilation
------------

When building the firmware the first time, the git submodule for "libemb" has to be initialized (since the "libemb" subdirectory
is a stub only otherwise). To initialize the "libemb" submodule, do the following (while in the top-level directory):

	git submodule init
	git submodule update

Then to build everything:

	make

The resulting firmware could be found in the `bin` directory.


Installing on the Targets
-------------------------

Flash the `firmware` to your target (MSP430) issue the following in the top-level directory:

	make flash-target FIRMWARE=msp430_ioexp_dio_firmware.elf


Usage
-----

TODO
