#include <iostream>
#include "ioexpdio.hpp"

using namespace std;
using namespace ioexp;

int main(void) 
{
	I2CMasterBus *mb = NULL;
	IOExpDio *ex = NULL;

	try
	{
		mb = new I2CMasterBus();
		ex = new IOExpDio(mb, 0x48);

		ex->reset();

		cout << "Type = " << (int)(ex->getType()) << endl;
		cout << "FW-Version = " << (int)(ex->getFirmwareVersion()) << endl;

		for(int pin = 0; pin < 8; pin++)
		{
			ex->configureOut(static_cast<IOExpPin>(1 << pin));
		}

		for(int pin = 0; pin < 8; pin++)
		{
			ex->writeOut(static_cast<IOExpPin>(1 << pin), IOExpLogVal::HIGH);
			sleep(1);
		}

		for(int pin = 0; pin < 8; pin++)
		{
			ex->writeOut(static_cast<IOExpPin>(1 << pin), IOExpLogVal::LOW);
			sleep(1);
		}
	}
	catch (exception& e)
	{
		cerr << "exception caught: " << e.what() << '\n';
	}

	if(ex != NULL) {
		delete ex;
	}

	if(mb != NULL) {
		delete mb;
	}

	return 0;
}
