#ifndef __I2CMASTER_HPP__
#define __I2CMASTER_HPP__

#include <vector>

namespace ioexp {

class I2CMasterBus
{
private:
	
	int fd; 

public:

	I2CMasterBus(const char *device = "/dev/i2c-0");

	~I2CMasterBus();

	void write(int slaveAddress, std::vector<unsigned char> data); 

	std::vector<unsigned char> read(int slaveAddress, unsigned char reg, int expectedLength);

	std::vector<unsigned char> xfer(int slaveAddress, std::vector<unsigned char> data, int expectedLength);

private:

	void openBus(const char *device);

	void closeBus();
};

}

#endif
