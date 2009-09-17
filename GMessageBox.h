
#ifndef __GMESSAGEBOX_H__
# define __GMESSAGEBOX_H__

#include "GString.h"
#if defined (WIN32) | defined (_WIN32) |  defined (__WIN32) | defined (WIN) | defined (WIN64) | defined (__WIN64)
#	include "windows.h"
#endif


class GMessageBox
{
	public:
		static void		Error(const GString &Title, const GString &Texte);
};

#endif
