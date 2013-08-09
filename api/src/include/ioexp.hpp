#ifndef __IOEXP_HPP__
#define __IOEXP_HPP__

#include <exception>

#include "i2cmaster.hpp"

namespace ioexp {

enum class IOExpType 
{ 
	UNKNOWN = 0x00,
	DIO = 0x01,
};

enum class IOExpPin
{ 
	P0 = 0b00000001,
	P1 = 0b00000010,
	P2 = 0b00000100,
	P3 = 0b00001000,
	P4 = 0b00010000,
	P5 = 0b00100000,
	P6 = 0b01000000,
	P7 = 0b10000000,
};

enum class IOExpLogVal
{ 
	LOW  = 0x00,
	HIGH = 0x01,
};

class IOExp
{
protected:

	I2CMasterBus *mbus;
	
	int address;
	
public:

	IOExp(I2CMasterBus *bus, int slaveAddress);

	~IOExp();

	IOExpType getType();

	unsigned char getFirmwareVersion(); 

	void reset();
};

}

#endif
