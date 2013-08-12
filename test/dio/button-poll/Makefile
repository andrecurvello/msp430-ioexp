CC=$(CROSS_COMPILE)gcc
CFLAGS=-Wall -Werror 
LDFLAGS=

all: button-poll 

button-poll: main.c
	$(CC) $(CFLAGS) main.c $(LDFLAGS) -o button-poll 

clean:
	rm -f button-poll 
