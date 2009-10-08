
#ifndef __FRENCHDAY_H__
# define __FRENCHDAY_H__

#include "DayInterface.h"
#include "GVector.hpp"

class FrenchDay : public DayInterface
{
	public:
		FrenchDay(void);
		~FrenchDay(void);

		GString		GetDay(unsigned int);
		GString		GetTruncateDay(unsigned int);


	private:
		GVector<GString>	_vec;
};

#endif
