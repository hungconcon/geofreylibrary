
#ifndef __ENGLISHMONTH_H__
# define __ENGLISHMONTH_H__

#include "MonthInterface.h"
#include "GVector.hpp"

class EnglishMonth : public MonthInterface
{
	public:
		EnglishMonth(void);
		~EnglishMonth(void);

		GString		GetMonth(unsigned int);
		GString		GetTruncateMonth(unsigned int);


	private:
		GVector<GString>	_vec;
};

#endif
