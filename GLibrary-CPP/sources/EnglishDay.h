
#ifndef __ENGLISHDAY_H__
# define __ENGLISHDAY_H__

#include "DayInterface.h"
#include "GVector.hpp"

class EnglishDay : public DayInterface
{
	public:
		EnglishDay(void);
		~EnglishDay(void);

		GString		GetDay(unsigned int);
		GString		GetTruncateDay(unsigned int);


	private:
		GVector<GString>	_vec;
};

#endif
