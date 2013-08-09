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
