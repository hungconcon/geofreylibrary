
#ifndef __GCHAR_H__
# define __GCHAR_H__

#include <iostream>
#include "GExport.h"

class GEXPORTED GChar
{
	public:
		GChar(void);
		GChar(char c);
		GChar(unsigned char c);
		GChar(const GChar &);
		GChar(const GChar *);
		GChar(int);
		~GChar(void);

		unsigned char GetChar(void) const;

		bool	IsLower(void) const;
		bool	IsUpper(void) const;
		bool	IsNull(void) const;
		bool	IsLetter(void) const;
		bool	IsAlpha(void) const;
		bool	IsDigit(void) const;
		bool	IsNumber(void) const;
		bool	IsSpace(void) const;
		bool	IsPrintable(void) const;
		bool	IsAlphaNumeric(void) const;

		GChar	&ToLower(void) const;
		GChar	&ToUpper(void) const;

		GChar	&operator++(void);
		GChar	&operator++(int);
		GChar	&operator--(void);
		GChar	&operator--(int);

		bool	operator==(const GChar &);
		bool	operator!=(const GChar &);
		bool	operator<(const GChar &);
		bool	operator<=(const GChar &);
		bool	operator>(const GChar &);
		bool	operator>=(const GChar &);
		GChar	&operator=(const GChar &);
		GChar	&operator=(char);
		GChar	&operator=(unsigned char);
		GChar	&operator=(int);

		friend std::ostream	&operator<<(std::ostream &out, GChar &);


	private:
		unsigned char	_c;
};

#endif
