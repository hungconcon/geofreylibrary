
#ifndef __GEXCEPTION_H__
# define __GEXCEPTION_H__


#include "GDeclaration.h"
#include "GExport.h"
#include <exception>

class GString;

class GEXPORTED GException : public std::exception
{
	public:
		GException(G::Exception);
		GException(const GString &Error);
		GException(const GString &Class, const GString &Error);
		~GException() throw();

		const char *what(void) const throw();

	private:
		const char *_str;
};

#endif
