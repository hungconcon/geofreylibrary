
#ifndef __GMAINWINDOW_H__
# define __GMAINWINDOW_H__

#include "GString.h"
#include "GThread.h"
#include "GMutex.h"
#include "GSleep.h"
#include "GSize.h"
#include "GWidget.h"
#include "GExport.h"

#if defined (GWIN)
#		include "windows.h"
#elif defined(GUNIX)
#		include <X11/Xlib.h>
#endif

class GMainWindow : public GWidget
{
	public:
		GMainWindow(void);
		~GMainWindow(void);	
		void			Destroy(void);
		void			SetTitle(const GString &);


	private:
		unsigned int	_x;
		unsigned int	_y; 

#if defined(GWIN)
	public:
		WNDCLASSEX		_classe;
#endif
		
};

#endif