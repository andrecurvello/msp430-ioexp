##
# Toplevel Makefile
#
# Stefan Wendler, sw@kaltpost.de
##

export TARCH=MSP430

BASEDIR 	= .
SRCDIR  	= dio/src
TESTDIR		= test
BINDIR		= bin
FIRMWARE   ?= firmware.elf
DEPLOYDIR	= deploy
TMPDIR		= /tmp
VERSION		= 0.1

all: target target-test

lib:
	make -C ./libemb/

target: lib
	make -C $(SRCDIR)

flash-target: target
	mspdebug rf2500 "prog $(BINDIR)/$(FIRMWARE)"

target-test:
	(cd $(TESTDIR)/dio/button-irq && make)
	(cd $(TESTDIR)/dio/button-irqcnt && make)
	(cd $(TESTDIR)/dio/button-poll && make)
	(cd $(TESTDIR)/dio/chasing && make)
	(cd $(TESTDIR)/api/output && make)

test-clean:
	make -C $(TESTDIR)/dio/button-irq clean
	make -C $(TESTDIR)/dio/button-irqcnt clean
	make -C $(TESTDIR)/dio/button-poll clean
	make -C $(TESTDIR)/dio/chasing clean
	make -C $(TESTDIR)/api/output clean

clean: test-clean
	make -C ./libemb/ clean
	make -C $(SRCDIR) clean
	rm -fr doc/gen
	rm -f bin/firmware.*
