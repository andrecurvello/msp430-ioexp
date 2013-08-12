CC=$(CROSS_COMPILE)g++
AR=$(CROSS_COMPILE)ar
CFLAGS=-Wall -Werror -std=c++0x -I./include 
LDFLAGS=
ARFLAGS=rcs

LIBDIR=../lib

SOURCES=i2cmaster.cpp ioexp.cpp ioexpdio.cpp 

OBJECTS=$(SOURCES:.cpp=.o)
LIBRARY=libioexp_i2capi.a

all: $(SOURCES) $(LIBRARY)
	
$(LIBRARY): $(OBJECTS)
	@#printf "  AR      $(subst $(shell pwd)/,,$(@))\n"
	mkdir -p $(LIBDIR)
	$(AR) $(ARFLAGS) $@ $^ && cp $(LIBRARY) $(LIBDIR)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(LIBRARY)
	rm -fr $(LIBDIR)
