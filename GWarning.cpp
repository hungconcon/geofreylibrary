
#include "GWarning.h"
#include "GString.h"

bool	GWarning::GWarningActivate = false;

void	GWarning::Warning(const GString &s)
{
	if (GWarningActivate)
		std::cerr << s << std::endl;
}

void	GWarning::Warning(const GString &Class, const GString &Method, const GString &Error)
{
	if (GWarningActivate)
		std::cerr << "Warning - " << Class << " - " << Method << " => " << Error << std::endl;
}

void	GWarning::Warning(const char *Class, const char *Method, const char *Error)
{
	if (GWarningActivate)
		std::cerr << "Warning - " << Class << " - " << Method << " => " << Error << std::endl;
}

void	GWarning::Activate(void)
{
	GWarningActivate = true;
}

void	GWarning::Desactivate(void)
{
	GWarningActivate = false;
}

bool	GWarning::IsActivate(void)
{
	return (GWarningActivate);
}
