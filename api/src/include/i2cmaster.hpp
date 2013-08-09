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
