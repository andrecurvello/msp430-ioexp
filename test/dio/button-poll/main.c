/*
 * This file is part of the MSP430 USCI I2C slave example.
 *
 * Copyright (C) 2012 Stefan Wendler <sw@kaltpost.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * This is the master part of the MSP430 I2C slave example. It sends
 * LED ON/OFF commands to the firmware making the build in LED on 
 * the MSP430 Launchpad blink. Pressing the build in button P1.3
 * changes the blink frequency. The program could be exited by
 * pressing CTRL+C. 
 */

#include <stdio.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>

/* I2C bus on which the MSP430 is connected */
#define I2C_DEV				"/dev/i2c-0"	

/* I2C 7-bit slave address */
#define I2C_SLAVE_ADDR		0x48

/* Commands */
#define CMD_SET_PDIR    0x00
#define CMD_GET_PIN     0x02
#define CMD_SET_REN     0x05
#define CMD_RESET       0xA0

/* indicates that main loop should be terminated */
int interrupted = 0;

/* signal handler */
static void signal_handler(int signal) {
	interrupted = 1;
}

/* wirte command (CMD_*) with given parameter (PAR_*) to slave */
static int i2c_write(int fd, unsigned char cmd, unsigned char par, unsigned char empty_par) {

    unsigned char buf[2];
    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[1];

    messages[0].addr  = I2C_SLAVE_ADDR;
    messages[0].flags = 0;
    messages[0].buf   = buf;

    buf[0] = cmd;

	if(empty_par == 1) {
    	messages[0].len = 1;
	}
	else {
    	messages[0].len = sizeof(buf);
    	buf[1] = par;
	}

    packets.msgs  	= messages;
    packets.nmsgs 	= 1;

    if(ioctl(fd, I2C_RDWR, &packets) < 0) {
        perror("data could not be send");
        return -1;
    }

    return 0;
}

/* read command (CMD_*) from slave */
static int i2c_read(int fd, unsigned char cmd, unsigned char *val) {

    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[2];

    messages[0].addr  = I2C_SLAVE_ADDR;
    messages[0].flags = 0;
    messages[0].len   = 1;
    messages[0].buf   = &cmd;

    messages[1].addr  = I2C_SLAVE_ADDR;
    messages[1].flags = I2C_M_RD;
    messages[1].len   = 1;
    messages[1].buf   = val;

    packets.msgs      = messages;
    packets.nmsgs     = 2;

    if(ioctl(fd, I2C_RDWR, &packets) < 0) {
        perror("data could not be send");
        return -1;
    }

    return 0;
}

int main(void) {

    int fd;

	unsigned char btn = 0;

    if (signal(SIGINT, signal_handler) == SIG_ERR) {
		printf("unable to register signal handler\n");
        return -1;
    }

    if ((fd = open(I2C_DEV, O_RDWR)) < 0) {
        perror("Unable to open i2c device");
		return -1;
    }

	printf("Press CTRL-C to end program.\n");

	/* reset */
	(void)i2c_write(fd, CMD_RESET, 0x00, 1);

	/* configure all ports as input */
	(void)i2c_write(fd, CMD_SET_PDIR, 0x00, 0);

	/* enable pull-up for all but p1.3 */
	(void)i2c_write(fd, CMD_SET_REN, 0xf7, 0);

	while(interrupted == 0) {

		(void)i2c_read(fd, CMD_GET_PIN, &btn);

		if(btn & 0b00000001) {
			printf("Button 0\n");
			usleep(100000);
		}
		if(btn & 0b00000010) {
			printf("Button 1\n");
			usleep(100000);
		}
		if(btn & 0b00000100) {
			printf("Button 2\n");
			usleep(100000);
		}
		if(!(btn & 0b00001000)) {
			printf("Button 3\n");
			usleep(100000);
		}
		if(btn & 0b00010000) {
			printf("Button 4\n");
			usleep(100000);
		}
		if(btn & 0b00100000) {
			printf("Button 5\n");
			usleep(100000);
		}
		if(btn & 0b01000000) {
			printf("Button 6\n");
			usleep(100000);
		}
		if(btn & 0b10000000) {
			printf("Button 7\n");
			usleep(100000);
		}

		usleep(50000);
	}

	/* reset */
	(void)i2c_write(fd, CMD_RESET, 0x00, 1);

    close(fd);

    return 0;
}
