#ifndef __IOEXPDIO_HPP__
#define __IOEXPDIO_HPP__

#include "ioexp.hpp"

namespace ioexp {

class IOExpDio : public IOExp
{
private:

	unsigned char pdir;

	unsigned char pren;

	unsigned char pout;

public:

	IOExpDio(I2CMasterBus *bus, int slaveAddress);

	void configureOut(IOExpPin pin);

	void configureIn(IOExpPin pin);

	void configureInPU(IOExpPin pin);

	void configureInPD(IOExpPin pin);

	void writeOut(IOExpPin pin, IOExpLogVal value);

	IOExpLogVal readIn(IOExpPin pin);	
};

}

#endif
