/*
 * This file is part of the mps430-ioexp project.
 *
 * Copyright (C) 2011 Stefan Wendler <sw@kaltpost.de>
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

		// reset MCU
		ex->reset();

		// read HW type
		cout << "Type = " << (int)(ex->getType()) << endl;
		
		// read FW version
		cout << "FW-Version = " << (int)(ex->getFirmwareVersion()) << endl;

		// configure all as input
		for(int pin = 0; pin < 8; pin++)
		{
			ex->configureInPD(static_cast<IOExpPin>(1 << pin));
		}

		// set all to high
		for(int pin = 0; pin < 8; pin++)
		{
			cout << "State of pin [" << pin << "] is ";
			
			if(ex->readIn(static_cast<IOExpPin>(1 << pin)) == IOExpLogVal::HIGH) {
				cout << "HIGH";
			}
			else {
				cout << "LOW";
			}
			
			cout << endl;
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
