
#ifndef __MONTHINTERFACE_H__
# define __MONTHINTERFACE_H__

#include "GString.h"

class MonthInterface
{
	public:
		virtual	~MonthInterface(void){};

		virtual GString	GetMonth(unsigned int) = 0;
		virtual GString	GetTruncateMonth(unsigned int) = 0;
};

#endif
