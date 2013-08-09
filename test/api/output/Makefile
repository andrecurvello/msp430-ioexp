CC=$(CROSS_COMPILE)g++
CFLAGS=-Wall -Werror -std=c++0x -I../../../api/src/include
LDFLAGS=-L../../../api/lib 
LIBS=-lioexp_i2capi

SOURCES=main.cpp

OBJECTS=$(SOURCES:.cpp=.o) 
EXECUTABLE=i2c_api_output

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm $(OBJECTS)
	rm $(EXECUTABLE)
