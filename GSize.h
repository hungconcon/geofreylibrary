
#ifndef __GSIZE_H__
# define __GSIZE_H__

class GSize
{
	public:
		GSize(unsigned int X, unsigned int Y);
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

#endif