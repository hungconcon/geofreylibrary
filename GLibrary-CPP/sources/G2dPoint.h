
#ifndef __G2DPOINT_H__
# define __G2DPOINT_H__

class G2dPoint
{
	public:
		G2dPoint(void);
		G2dPoint(double X, double Y);
		G2dPoint(const G2dPoint &Point);
		~G2dPoint(void);

		double	GetX(void) const;
		double	GetY(void) const;

	protected:
		double	_x;
		double	_y;
};

#endif
