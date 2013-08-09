#include <stdio.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <iostream>

#include "ioexpexception.hpp"
#include "i2cmaster.hpp"

// #define TRACE	std::cout << __func__ << std::endl;
#define TRACE

ioexp::I2CMasterBus::I2CMasterBus(const char *device)
{
	TRACE

	fd = -1;

	openBus(device);
}

ioexp::I2CMasterBus::~I2CMasterBus()
{
	TRACE

	closeBus();
}

void ioexp::I2CMasterBus::write(int slaveAddress, std::vector<unsigned char> data) 
{
	TRACE

    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[1];

    messages[0].addr  = slaveAddress;
    messages[0].flags = 0;
  	messages[0].len   = data.size();
    messages[0].buf   = &data[0];

    packets.msgs  	= messages;
    packets.nmsgs 	= 1;

    if(ioctl(fd, I2C_RDWR, &packets) < 0) {
        throw IOExpException("Unable to send data");
    }
}

void flushfd(int fd) 
{
	unsigned char b; 
	while(read(fd, &b, 1) > 0) printf(".");
}

std::vector<unsigned char> ioexp::I2CMasterBus::read(int slaveAddress, unsigned char reg, int expectedLength)
{
	TRACE

	unsigned char *buf = new unsigned char(expectedLength);

    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[2];

	flushfd(fd);

    messages[0].addr  = slaveAddress;
    messages[0].flags = 0;
    messages[0].len   = 1;
    messages[0].buf   = &reg;

    messages[1].addr  = slaveAddress;
    messages[1].flags = I2C_M_RD;
    messages[1].len   = expectedLength;
    messages[1].buf   = buf;

    packets.msgs      = messages;
    packets.nmsgs     = 2;

    if(ioctl(fd, I2C_RDWR, &packets) < 0) {
        throw IOExpException("Unable to send data");
    }
	
	std::vector<unsigned char> res(buf, buf + expectedLength);

	delete buf;

	return res;
}

std::vector<unsigned char> ioexp::I2CMasterBus::xfer(int slaveAddress, std::vector<unsigned char> data, int expectedLength)
{
	TRACE

	unsigned char *buf = new unsigned char(expectedLength);

    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[2];

    messages[0].addr  = slaveAddress;
    messages[0].flags = 0;
  	messages[0].len   = data.size();
    messages[0].buf   = &data[0];

    messages[1].addr  = slaveAddress;
    messages[1].flags = I2C_M_RD;
    messages[1].len   = expectedLength;
    messages[1].buf   = buf;

    packets.msgs      = messages;
    packets.nmsgs     = 2;

    if(ioctl(fd, I2C_RDWR, &packets) < 0) {
        throw IOExpException("Unable to send data");
    }
	
	std::vector<unsigned char> res(buf, buf + expectedLength);

	delete buf;

	return res;
}	

void ioexp::I2CMasterBus::openBus(const char *device)
{
	TRACE

    if((fd = open(device, O_RDWR)) < 0) {
        throw IOExpException("Unable to open i2c device");
    }
}

void ioexp::I2CMasterBus::closeBus()
{
	TRACE

	if(fd > -1) {
		close(fd);
	}	
}

