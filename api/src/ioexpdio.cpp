#include <stdio.h>
#include <unistd.h>

#include "ioexpdio.hpp"

/* Commands */
#define CMD_SET_PDIR    0x00
#define CMD_SET_POUT    0x01
#define CMD_GET_PIN     0x02
#define CMD_SET_PIR     0x03
#define CMD_GET_PIR     0x04
#define CMD_SET_REN     0x05
#define CMD_GET_PIRC    0x06

ioexp::IOExpDio::IOExpDio(ioexp::I2CMasterBus *bus, int slaveAddress) : ioexp::IOExp(bus, slaveAddress)
{
	pdir = 0xFF;
	pren = 0x00;
	pout = 0x00;
}

void ioexp::IOExpDio::configureOut(ioexp::IOExpPin pin)
{
	pdir |= (unsigned char)pin;

	std::vector<unsigned char> msg1 = {CMD_SET_PDIR, pdir};
	mbus->write(address, msg1);

	pren &= ~(unsigned char)pin;

	std::vector<unsigned char> msg2 = {CMD_SET_REN, pren};
	mbus->write(address, msg2);
}

void ioexp::IOExpDio::configureIn(ioexp::IOExpPin pin)
{
	pdir &= ~(unsigned char)pin;

	std::vector<unsigned char> msg1 = {CMD_SET_PDIR, pdir};
	mbus->write(address, msg1);

	pren &= ~(unsigned char)pin;
/*
	std::vector<unsigned char> msg2 = {CMD_SET_REN, pren};
	mbus->write(address, msg2);

	writeOut(pin, ioexp::IOExpLogVal::LOW);
*/
}

void ioexp::IOExpDio::configureInPU(ioexp::IOExpPin pin)
{
	pdir &= ~(unsigned char)pin;

	std::vector<unsigned char> msg1 = {CMD_SET_PDIR, pdir};
	mbus->write(address, msg1);
	
	pren |= (unsigned char)pin;

	std::vector<unsigned char> msg2 = {CMD_SET_REN, pren};
	mbus->write(address, msg2);

	writeOut(pin, ioexp::IOExpLogVal::HIGH);

}

void ioexp::IOExpDio::configureInPD(ioexp::IOExpPin pin)
{
	pdir &= ~(unsigned char)pin;

	std::vector<unsigned char> msg1 = {CMD_SET_PDIR, pdir};
	mbus->write(address, msg1);
	
	pren |= (unsigned char)pin;

	std::vector<unsigned char> msg2 = {CMD_SET_REN, pren};
	mbus->write(address, msg2);

	writeOut(pin, ioexp::IOExpLogVal::LOW);
}

void ioexp::IOExpDio::writeOut(ioexp::IOExpPin pin, ioexp::IOExpLogVal value)
{
	if(value == ioexp::IOExpLogVal::HIGH) {
		pout |= (unsigned char)pin;
	}
	else {
		pout &= ~(unsigned char)pin;
	}

	std::vector<unsigned char> msg1 = {CMD_SET_POUT, pout};
	mbus->write(address, msg1);
}

ioexp::IOExpLogVal ioexp::IOExpDio::readIn(ioexp::IOExpPin pin)	
{
	std::vector<unsigned char> res = mbus->read(address, CMD_GET_PIN, 1);

	printf("res: %02x\n", res[0]);

	if(res[0] & (unsigned char)pin) {
		return ioexp::IOExpLogVal::HIGH;
	}

	return ioexp::IOExpLogVal::LOW;
}
