
#ifndef __GCOLOR_H__
# define __GCOLOR_H__

class GColor
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


