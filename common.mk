##
# Common settings for Makefiles
#
# Stefan Wendler, sw@kaltpost.de
##
#
# compiler prefix
PREFIX  ?= msp430-

CC			 = $(PREFIX)gcc
LD			 = $(PREFIX)gcc
OBJCOPY		 = $(PREFIX)objcopy
OBJDUMP		 = $(PREFIX)objdump

INCDIR		+= -I./include 
CFLAGS		+= -Os -g -mmcu=msp430g2553 -Wall -Wextra $(INCDIR) 
LDFLAGS     += -mmcu=msp430g2553 $(LIBDIR) $(LIBS)

# where to put generated binaries to
BINDIR		?= ../../bin

.SUFFIXES: .elf .bin .hex .srec .list .images
.SECONDEXPANSION:
.SECONDARY:

all: images

images: $(BINARY).images

%.images: %.bin %.hex %.srec %.list
	@#echo "*** $* images generated ***"

%.bin: %.elf
	@#printf "  OBJCOPY $(*).bin\n"
	$(OBJCOPY) -Obinary $(*).elf $(*).bin && cp $(*).bin $(BINDIR)/$(TARGET).bin

%.hex: %.elf
	@#printf "  OBJCOPY $(*).hex\n"
	$(OBJCOPY) -Oihex $(*).elf $(*).hex && cp $(*).hex $(BINDIR)/$(TARGET).hex

%.srec: %.elf
	@#printf "  OBJCOPY $(*).srec\n"
	$(OBJCOPY) -Osrec $(*).elf $(*).srec && cp $(*).srec $(BINDIR)/$(TARGET).srec

%.list: %.elf
	@#printf "  OBJDUMP $(*).list\n"
	$(OBJDUMP) -S $(*).elf > $(*).list && cp $(*).list $(BINDIR)/$(TARGET).list

%.elf: $(OBJS) $(LDSCRIPT)
	@#printf "  LD      $(subst $(shell pwd)/,,$(@))\n"
	$(LD) $(OBJS) $(LDFLAGS) -o $(*).elf && cp $(*).elf $(BINDIR)/$(TARGET).elf

%.o: %.c Makefile
	@#printf "  CC      $(subst $(shell pwd)/,,$(@))\n"
	$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.cpp Makefile
	@#printf "  CC      $(subst $(shell pwd)/,,$(@))\n"
	$(CC) $(CFLAGS) -o $@ -c $<

SRC = $(wildcard *.c)
HDR = $(wildcard include/*.h)

style:
	$(STYLER) $(STYLERFLAGS) $(SRC)
	$(STYLER) $(STYLERFLAGS) $(HDR)

clean:
	rm -f *.o
	rm -f *.d
	rm -f *.elf
	rm -f *.bin
	rm -f *.hex
	rm -f *.srec
	rm -f *.list
	rm -f *.orig

.PHONY: images clean

