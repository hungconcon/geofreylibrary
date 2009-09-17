
#ifndef __GDAYINSTANCE_H__
# define __GDAYINSTANCE_H__

#include "GDeclaration.h"
#include "DayInterface.h"
#include "FrenchDay.h"
#include "EnglishDay.h"
#include "GWarning.h"
#include "GException.h"


class GDayInstance
{
	public:
		static DayInterface	*GetInstance(G::LanguageOption Language = G::FRENCH);
};

#endif
