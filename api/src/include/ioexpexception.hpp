#ifndef __IOEXPEXCEPTION_HPP__
#define __IOEXPEXCEPTION_HPP__

#include <exception>

namespace ioexp {

class IOExpException : public std::exception
{
private:

	const char *message; 

public:

	IOExpException(const char *aMessage)
	{
		message = aMessage;
	}

	virtual const char* what() const throw()
	{
		return message;
	}
};

}

#endif
