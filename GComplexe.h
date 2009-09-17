#ifndef __G_COMPLEXE__
# define __G_COMPLEXE__

#include "GFraction.h"

class	GComplexe
{
	public:
		GComplexe(const GFraction &, const GFraction &);
		~GComplexe(void);

		GFraction		&Im(void);
		GFraction		&Re(void);

 private:
  GFraction		_im;
  GFraction		_re;
};

#endif
