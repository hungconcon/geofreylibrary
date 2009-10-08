
#ifndef __GCOLOR_H__
# define __GCOLOR_H__

#include "GExport.h"

struct GColorRGB
{
	char	_red;
	char	_green;
	char	_blue;
};

class GEXPORTED GColor
{
	public:
		GColor(int R, int G, int B);
		~GColor(void);

	private:
		int		_R;
		int		_G;
		int		_B;
};

#endif


