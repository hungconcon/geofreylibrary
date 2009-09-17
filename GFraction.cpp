
#include "GFraction.h"

GFraction::GFraction(void)
{

}

GFraction::GFraction(int num, int den)
{
	this->_num = num;
	this->_den = den;
}

GFraction::~GFraction(void)
{
	
}

bool		GFraction::IsPositive(void) const
{
	if (this->_num > 0 && this->_den > 0)
		return (true);
	if (this->_num < 0 && this->_den < 0)
		return (true);
	return (false);
}

bool		GFraction::IsNegative(void) const
{
	if (this->_num > 0 && this->_den > 0)
		return (false);
	if (this->_num < 0 && this->_den < 0)
		return (false);
	return (true);
}

void		GFraction::Simplify(void)
{
	int a = this->_num;
	int b = this->_den;
	if (a < 0)
		a *= -1;
	if (b < 0)
		b *= -1;
	int pgcd = GAlgo::PGCD(a, b);
	this->_num /= pgcd;
	this->_den /= pgcd;
}

int			GFraction::GetDenominator(void) const
{
	return (this->_den);
}

int			GFraction::GetNumerator(void) const
{
	return (this->_num);
}


GFraction	&GFraction::operator=(const GFraction &f)
{
	this->_den = f._den;
	this->_num = f._num;
	return (*this);
}

GFraction	&GFraction::operator*=(const GFraction &f)
{
	this->Simplify();
	this->_den *= f._den;
	this->_num *= f._num;
	this->Simplify();
	return (*this);
}

GFraction	&GFraction::operator/=(const GFraction &f)
{
	this->Simplify();
	this->_den *= f._num;
	this->_num *= f._den;
	this->Simplify();
	return (*this);
}

GFraction	&GFraction::operator+=(const GFraction &f)
{
	this->Simplify();
	this->_den *= f._den;
	this->_num *= f._den;
	int num = f._num * this->_den;
	this->_num += num;
	this->Simplify();
	return (*this);
}

GFraction	&GFraction::operator-=(const GFraction &f)
{
	this->Simplify();
	this->_den *= f._den;
	this->_num *= f._den;
	int num = f._num * this->_den;
	this->_num -= num;
	this->Simplify();
	return (*this);
}
