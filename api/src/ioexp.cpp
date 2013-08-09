#include "ioexp.hpp"

#define CMD_RESET       0xA0
#define CMD_FW_TYPE		0xF0
#define CMD_FW_VERSION	0xF1

ioexp::IOExp::IOExp(ioexp::I2CMasterBus *bus, int slaveAddress)
{
	mbus = bus;

	address = slaveAddress;
}

ioexp::IOExp::~IOExp()
{
}

ioexp::IOExpType ioexp::IOExp::getType()
{
	std::vector<unsigned char> res = mbus->read(address, CMD_FW_TYPE, 1);

	switch(res[0]) {
		case 0x01: return ioexp::IOExpType::DIO;
	}

	return ioexp::IOExpType::UNKNOWN;
}

unsigned char ioexp::IOExp::getFirmwareVersion() 
{
	std::vector<unsigned char> res = mbus->read(address, CMD_FW_VERSION, 1);

	return res[0];
}

void ioexp::IOExp::reset()
{
	std::vector<unsigned char> msg = {CMD_RESET};
	mbus->write(address, msg);
}

