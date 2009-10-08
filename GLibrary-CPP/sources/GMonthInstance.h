
#ifndef __GMONTHINSTANCE_H__
# define __GMONTHINSTANCE_H__

#include "G.h"
#include "DayInterface.h"
#include "FrenchMonth.h"
#include "EnglishMonth.h"
#include "GWarning.h"
#include "GException.h"

class GMonthInstance
{
	public:
		static MonthInterface	*GetInstance(G::LanguageOption = G::FRENCH);
};

#endif
