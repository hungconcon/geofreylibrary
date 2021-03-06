
#ifndef __GSIZE_H__
# define __GSIZE_H__

#include "GExport.h"

class GEXPORTED GSize
{
	public:
		GSize(unsigned int X, unsigned int Y);
		GSize(const GSize &Size);
		GSize(void);
		~GSize(void);

		void			SetX(unsigned int X);
		void			SetY(unsigned int Y);
		void			SetXY(unsigned int X, unsigned int Y);
		unsigned int	GetX(void) const;
		unsigned int	GetY(void) const;

		
		GSize			&operator=(const GSize &Size);
	

	private:
		unsigned int _x;
		unsigned int _y;
};

typedef GSize GPosition;
typedef GSize GPoint;

#endif