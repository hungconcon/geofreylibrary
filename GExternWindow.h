
#ifndef __GEXTERNWINDOW_H__
# define __GEXTERNWINDOW_H__

#if defined (WIN32) | defined (_WIN32) |  defined (__WIN32) | defined (WIN) | defined (WIN64) | defined (__WIN64)
#		include "windows.h"
#endif

#include "GString.h"
#include "GWidget.h"

class GExternWindow : public GWidget
{
	public:
		GExternWindow(void);
		~GExternWindow(void);

		bool	Find(const GString &WindowName);
		bool	SetTittle(const GString &);
};



#endif