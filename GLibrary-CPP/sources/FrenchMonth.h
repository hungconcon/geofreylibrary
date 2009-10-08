
#ifndef __FRENCHMONTH_H__
# define __FRENCHMONTH_H__

#include "MonthInterface.h"
#include "GVector.hpp"

class FrenchMonth : public MonthInterface
{
	public:
		FrenchMonth(void);
		~FrenchMonth(void);

		GString		GetMonth(unsigned int);
		GString		GetTruncateMonth(unsigned int);


	private:
		GVector<GString>	_vec;
};

#endif
