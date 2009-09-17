
#ifndef __GEXTERNWINDOW_H__
# define __GEXTERNWINDOW_H__

#if defined (WIN32) | defined (_WIN32) |  defined (__WIN32) | defined (WIN) | defined (WIN64) | defined (__WIN64)
#		include "windows.h"
#endif

#include "GString.h"

class GExternWindow
{
	public:
		GExternWindow(void);
		~GExternWindow(void);

		bool	Find(const GString &WindowName);
		bool	SetTittle(const GString &);
		bool	Hide(void);
		bool	Show(void);
		bool	IsVisible(void);
		bool	Destroy(void);

	private:
		HWND	_handle;
};



#endif