##
# Toplevel Makefile
#
# Stefan Wendler, sw@kaltpost.de
##

export TARCH=MSP430

BASEDIR 	= .
FIRMWARE   ?= ./bin/msp430_ioexp_dio_firmware.elf
VERSION		= 0.1
CLIENV		= mips

all: dio dio-test client-api client-api-test

lib:
	make -C ./libemb/

lib-clean:
	make -C ./libemb/ clean

dio: lib
	make -C dio/src

dio-clean: lib
	make -C dio/src clean
	
dio-test: dio
	make -C ./test/dio/button-irq
	make -C ./test/dio/button-irqcnt
	make -C ./test/dio/button-poll
	make -C ./test/dio/chasing

dio-test-clean:
	make -C ./test/dio/button-irq clean
	make -C ./test/dio/button-irqcnt clean
	make -C ./test/dio/button-poll clean
	make -C ./test/dio/chasing clean

client-api:
	test -f setenv-$(CLIENV).sh && . ./setenv-$(CLIENV).sh
	make -C ./api/src

client-api-clean:
	make -C ./api/src clean
	
client-api-test: client-api
	make -C ./test/api/output
	make -C ./test/api/input
	make -C ./test/api/inout
		
client-api-test-clean:
	make -C ./test/api/output clean
	make -C ./test/api/input clean
	make -C ./test/api/inout clean

flash-target: dio
	mspdebug rf2500 "prog $(FIRMWARE)"
	
clean: dio-clean dio-test-clean client-api-clean client-api-test-clean lib-clean
	rm -fr doc/gen
	rm -f  bin/*
