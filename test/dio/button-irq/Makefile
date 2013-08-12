CC=$(CROSS_COMPILE)gcc
CFLAGS=-Wall -Werror 
LDFLAGS=

all: button-irq 

button-irq: main.c
	$(CC) $(CFLAGS) main.c $(LDFLAGS) -o button-irq 

clean:
	rm -f button-irq 
