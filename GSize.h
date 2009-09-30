
#ifndef __GSIZE_H__
# define __GSIZE_H__

class GSize
{
	public:
		GSize(unsigned int X, unsigned int Y);
		GSize(const GSize &Size);
		GSize(void);
		~GSize(void);

		void			SetX(unsigned int X);
		void			SetY(unsigned int Y);
		unsigned int	GetX(void) const;
		unsigned int	GetY(void) const;

	private:
		unsigned int _x;
		unsigned int _y;
};

typedef GSize GPosition;
typedef GSize GPoint;

#endif