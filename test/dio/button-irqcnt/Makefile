CC=$(CROSS_COMPILE)gcc
CFLAGS=-Wall -Werror 
LDFLAGS=

all: button-irqcnt 

button-irqcnt: main.c
	$(CC) $(CFLAGS) main.c $(LDFLAGS) -o button-irqcnt 

clean:
	rm button-irqcnt 
