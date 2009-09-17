
#ifndef __GWARNING_H__
# define __GWARNING_H__

#include "GExport.h"
class GString;

class GEXPORTED GWarning
{
	public:
		static void		Activate(void);
		static void		Desactivate(void);
		static bool		IsActivate(void);
		static void		Warning(const GString &Message);
		static void		Warning(const GString &Class, const GString &Method, const GString &Error);
		static void		Warning(const char *Class, const char *Method, const char *Error);

private:
	static bool		GWarningActivate;
};

#endif
