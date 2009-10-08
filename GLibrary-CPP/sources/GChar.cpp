
#include "GChar.h"

GChar::GChar(void)
{
	this->_c = 0;
}

GChar::GChar(char c)
{
	this->_c = c;
}
GChar::GChar(unsigned char c)
{
	this->_c = c;
}

GChar::GChar(const GChar &g)
{
	this->_c = g._c;
}
GChar::GChar(int c)
{
	this->_c = (char)c;
}
GChar::~GChar(void)
{

}

bool	GChar::IsNull(void) const
{
	if (this->_c == 0)
		return (true);
	return (false);
}
bool	GChar::IsLower(void) const
{
	if (this->_c >= 'a' && this->_c <= 'z')
		return (true);
	return(false);
}
bool	GChar::IsUpper(void) const
{
	if (this->_c >= 'A' && this->_c <= 'Z')
		return (true);
	return(false);
}
bool	GChar::IsLetter(void) const
{
	if ((this->_c >= 'A' && this->_c <= 'Z') || (this->_c >= 'a' && this->_c <= 'z'))
		return (true);
	return (false);
}
bool	GChar::IsAlpha(void) const
{
	if ((this->_c >= 'A' && this->_c <= 'Z') || (this->_c >= 'a' && this->_c <= 'z'))
		return (true);
	return (false);
}
bool	GChar::IsDigit(void) const
{
	if (this->_c >= '0' && this->_c <= '9')
		return (true);
	return(false);
}
bool	GChar::IsNumber(void) const
{
	if (this->_c >= '0' && this->_c <= '9')
		return (true);
	return(false);
}
bool	GChar::IsSpace(void) const
{
	if (this->_c == ' ')
		return (true);
	return (false);
}
bool	GChar::IsPrintable(void) const
{
	if (this->_c >= 32 && this->_c != 127 && this->_c != '\n' && this->_c != '\t')
		return (true);
	return (false);
}

bool	GChar::IsAlphaNumeric(void) const
{
	if (this->IsDigit() || this->IsLetter())
		return (true);
	return (false);
}
// METHODES QChar

GChar	&GChar::ToLower(void) const
{
	if (this->_c >= 'A' && this->_c <= 'Z')
		return (*(new GChar(this->_c + 32)));
	return (*(new GChar(this->_c)));
}
GChar	&GChar::ToUpper(void) const
{
	if (this->_c >= 'a' && this->_c <= 'z')
		return (*(new GChar(this->_c - 32)));
	return (*(new GChar(this->_c)));
}

unsigned char GChar::GetChar(void) const
{
	return (this->_c);
}
//SURCHARGE


GChar	&GChar::operator++(void)
{
	++(this->_c);
	return(*this);
}
GChar	&GChar::operator++(int)
{
	++(this->_c);
	return(*this);
}
GChar	&GChar::operator--(void)
{
	--(this->_c);
	return(*this);
}
GChar	&GChar::operator--(int)
{
	--(this->_c);
	return(*this);
}
bool	GChar::operator==(const GChar &c)
{
	if (this->_c == c._c)
		return (true);
	return (false);
}
bool	GChar::operator!=(const GChar &c)
{
	if (this->_c == c._c)
		return (false);
	return (true);
}

bool	GChar::operator<(const GChar &c)
{
	if (this->_c < c._c)
		return (true);
	return (false);
}
bool	GChar::operator>(const GChar &c)
{
	if (this->_c > c._c)
		return (true);
	return (false);
}
bool	GChar::operator<=(const GChar &c)
{
	if (this->_c <= c._c)
		return (true);
	return (false);
}
bool	GChar::operator>=(const GChar &c)
{
	if (this->_c >= c._c)
		return (true);
	return (false);
}
std::ostream	&operator<<(std::ostream &out, GChar &c)
{
	out << c._c;
	return (out);
}


GChar	&GChar::operator=(const GChar &c)
{
	this->_c = c._c;
	return (*this);
}
GChar	&GChar::operator=(char c)
{
	this->_c = c;
	return (*this);
}
GChar	&GChar::operator=(unsigned char c)
{
	this->_c = c;
	return (*this);
}
GChar	&GChar::operator=(int c)
{
	this->_c = (int)c;
	return (*this);
}
