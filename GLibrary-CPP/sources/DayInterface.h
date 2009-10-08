
#ifndef __DAYINTERFACE_H__
# define __DAYINTERFACE_H__

#include "GString.h"

class DayInterface
{
	public:
		virtual	~DayInterface(void){};

		virtual GString	GetDay(unsigned int) = 0;
		virtual GString	GetTruncateDay(unsigned int) = 0;
};

#endif
