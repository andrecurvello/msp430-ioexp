TODO
=============================


Project Directory Layout
------------------------

The top-level directory structure of the project looks something like this:

* `Makefile` 		toplevel Make file
* `README.md`		this README
* `setenv.sh`		source to set cross-compile environment
* `master`			sample master code (e.g. to run on the TP-Link MR3020)	
* `slave`			sample slave firmware to tun on the MSP430G2553	


Prerequisites
-------------


Compilation
------------

Installing on the Targets
-------------------------

Flash the `firmware` to your target (MSP430):

	mspdebug rf2500 "prog deploy/firmware"


Usage
-----


