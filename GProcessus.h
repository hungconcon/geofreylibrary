
#ifndef __GProcessus_H__
# define __GProcessus_H__

#include "GString.h"

#if defined (GWIN)
#		include "windows.h"
#else

#endif

class GProcessus
{
	public:
		static void		Run(const GString &, const GString & = "");
		//static QString		list(void);
	private:

};

#endif
