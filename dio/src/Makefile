BINARY	 = firmware
OBJS	+= main.o cmd.o
INCDIR  += -I../../libemb/libi2c/src/include
LIBDIR  += -L../../libemb/libi2c/lib 
LIBS	+= -li2c
TARGET   = msp430_ioexp_dio_$(BINARY)

include ../../common.mk
