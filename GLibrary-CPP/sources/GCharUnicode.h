
#ifndef		__GCHARUNICODE_H__
# define	__GCHARUNICODE_H__

#include <iostream>
#include "GExport.h"

class GEXPORTED GCharUnicodeUnicode
{
	public:
		GCharUnicode(void);
		GCharUnicode(char c);
		GCharUnicode(unsigned char c);
		GCharUnicode(const GCharUnicode &);
		GCharUnicode(int);
		~GCharUnicode(void);

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

		GCharUnicode	&ToLower(void) const;
		GCharUnicode	&ToUpper(void) const;

		GCharUnicode	&operator++(void);
		GCharUnicode	&operator++(int);
		GCharUnicode	&operator--(void);
		GCharUnicode	&operator--(int);

		bool			operator==(const GCharUnicode &);
		bool			operator!=(const GCharUnicode &);
		bool			operator<(const GCharUnicode &);
		bool			operator<=(const GCharUnicode &);
		bool			operator>(const GCharUnicode &);
		bool			operator>=(const GCharUnicode &);
		GCharUnicode	&operator=(const GCharUnicode &);
		GCharUnicode	&operator=(char);
		GCharUnicode	&operator=(unsigned char);
		GCharUnicode	&operator=(int);

		friend std::ostream	&operator<<(std::ostream &out, GCharUnicode &);


	private:
		unsigned char	_c;
};

#endif
