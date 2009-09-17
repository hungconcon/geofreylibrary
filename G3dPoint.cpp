
#include "G3dPoint.h"

G3dPoint::G3dPoint(void) : G2dPoint()
{
	this->_z = 0;
}

G3dPoint::G3dPoint(const G3dPoint &p) : G2dPoint(p)
{
	this->_z = p._z;
}

G3dPoint::G3dPoint(double x, double y, double z) : G2dPoint(x, y)
{
	this->_z = z;
}

G3dPoint::~G3dPoint(void)
{

}

double	G3dPoint::GetZ(void) const
{
	return (this->_z);
}
