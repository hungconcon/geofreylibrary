
#ifndef __GFRACTION_H__
# define __GFRACTION_H__

#include "GAlgo.h"
#include "GString.h"

class GFraction
{
	public:
		GFraction(void);
		GFraction(int, int = 1);
		~GFraction(void);

		bool	IsPositive(void) const;
		bool	IsNegative(void) const;
		void	Simplify(void);
		int		GetNumerator(void) const;
		int		GetDenominator(void) const;

		GFraction	&operator=(const GFraction &);
		GFraction	&operator+=(const GFraction &);
		GFraction	&operator-=(const GFraction &);
		GFraction	&operator/=(const GFraction &);
		GFraction	&operator*=(const GFraction &);

	private:
		int		_den;
		int		_num;
};

#endif
