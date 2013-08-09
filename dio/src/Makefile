BINARY	 = firmware
OBJS	+= main.o cmd.o
INCDIR  += -I../../libemb/libi2c/src/include
INCDIR  += -I../../libemb/libserial/src/include
INCDIR  += -I../../libemb/libconio/src/include
LIBDIR  += -L../../libemb/libi2c/lib 
LIBDIR  += -L../../libemb/libserial/lib 
LIBDIR  += -L../../libemb/libconio/lib 
LIBS	+= -li2c -lserial -lconio
LIBS	+= -li2c 
TARGET   = msp430_ioexp_dio_$(BINARY)

include ../../common.mk
