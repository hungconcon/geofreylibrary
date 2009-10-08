
#include "G2dPoint.h"

G2dPoint::G2dPoint(void)
{
	this->_x = 0;
	this->_y = 0;
}

G2dPoint::G2dPoint(double x, double y)
{
	this->_x = x;
	this->_y = y;
}

G2dPoint::G2dPoint(const G2dPoint &p)
{
	this->_x = p._x;
	this->_y = p._y;
}

G2dPoint::~G2dPoint(void)
{
}

double	G2dPoint::GetX(void) const
{
	return (this->_x);
}

double	G2dPoint::GetY(void) const
{
	return (this->_y);
}
