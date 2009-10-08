
#ifndef __G3DPOINT_H__
# define __G3DPOINT_H__

#include "G2dPoint.h"

class G3dPoint : public G2dPoint
{
	public:
		G3dPoint(void);
		G3dPoint(const G3dPoint &);
		G3dPoint(double X, double Y, double Z);
		~G3dPoint(void);

		double	GetZ(void) const;

	protected:
		double	_z;
};

#endif
