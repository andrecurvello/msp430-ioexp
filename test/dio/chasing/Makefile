CC=$(CROSS_COMPILE)gcc
CFLAGS=-Wall -Werror 
LDFLAGS=

all: chasing 

chasing: main.c
	$(CC) $(CFLAGS) main.c $(LDFLAGS) -o chasing 

clean:
	rm -f chasing
