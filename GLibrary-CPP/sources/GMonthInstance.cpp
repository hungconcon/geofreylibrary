
#include "GMonthInstance.h"

MonthInterface	*GMonthInstance::GetInstance(G::LanguageOption op)
{
	if (op == G::FRENCH)
		return (new FrenchMonth());
	if (op == G::ENGLISH)
		return (new EnglishMonth());
	GWarning::Warning("GMonthInstance", "GetInstance(G::LanguageOption)", "There is no traduction of months for this language !");	
	throw GException(G::CANNOT_TRADUCT_THIS_LANGUAGE);
	return (NULL);
}

