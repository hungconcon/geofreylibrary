
#include "GException.h"
#include "GString.h"


GException::GException(G::Exception)
{
		
}

GException::GException(const GString &Error)
{
	this->_str = Error.ToChar();
}

GException::GException(const GString &Class, const GString &Error)
{
	this->_str = GString(Class + " - " + Error).ToChar();
}

GException::~GException() throw()
{

}

const char *GException::what(void) const throw()
{
	return (this->_str);
}
