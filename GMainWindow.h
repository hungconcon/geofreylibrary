
#ifndef __GMAINWINDOW_H__
# define __GMAINWINDOW_H__

#include "GString.h"
#include "GThread.h"
#include "GMutex.h"
#include "GSleep.h"
#include "GSize.h"
#include "GWidget.h"


#if defined (GWIN)
#		include "windows.h"
#endif

class GMainWindow : public GWidget
{
	public:
		GMainWindow(void);
		~GMainWindow(void);	
		
		void			SetTitle(const GString &);

	private:
		unsigned int	_x;
		unsigned int	_y; 

	private:

		//LRESULT CALLBACK MainProc(HWND Dlg,UINT message,WPARAM wParam,LPARAM lParam);

	public:
		WNDCLASSEX		_classe;

		
};

#endif