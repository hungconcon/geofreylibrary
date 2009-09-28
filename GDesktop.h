
#ifndef __GDESKTOP_H__
# define __GDESKTOP_H__

#include "GExport.h"
#if defined (GWIN)
#		include "windows.h"
#		include "Winuser.h"
#		pragma comment(lib, "User32.lib")
#		pragma comment(lib, "winmm.lib")
#endif

class GEXPORTED GDesktop
{
	public:
		static void		HideIcons(void);
		static void		ShowIcons(void);
		static void		ChangeIconsStyle(void);
};

#endif
