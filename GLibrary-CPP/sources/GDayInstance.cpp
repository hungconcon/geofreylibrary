
#include "GDayInstance.h"

DayInterface	*GDayInstance::GetInstance(G::LanguageOption op)
{
	if (op == G::FRENCH)
		return (new FrenchDay());
	if (op == G::ENGLISH)
		return (new EnglishDay());
	GWarning::Warning("GDayInstance", "GetInstance(G::LanguageOption)", "There is no traduction of days for this language !");
	throw GException(G::CANNOT_TRADUCT_THIS_LANGUAGE);
	return (NULL);
}

