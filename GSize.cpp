
#include "GSize.h"

GSize::GSize(unsigned int X, unsigned int Y)
{
	this->_x = X;
	this->_y = Y;
}

GSize::GSize(void)
{
	this->_x = 0;
	this->_y = 0;
}

GSize::GSize(const GSize &Size)
{
	this->_x = Size.GetX();
	this->_y = Size.GetY();
}

GSize::~GSize(void)
{

}

void	GSize::SetX(unsigned int X)
{
	this->_x = X;
}

void	GSize::SetY(unsigned int Y)
{
	this->_y = Y;
}

unsigned int GSize::GetX(void) const
{
	return (this->_x);
}

unsigned int GSize::GetY(void) const
{
	return (this->_y);
}