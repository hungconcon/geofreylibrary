
#ifndef __GDESKTOP_H__
# define __GDESKTOP_H__

#if defined (GWIN)
#		include "windows.h"
#		include "Winuser.h"
#		pragma comment(lib, "User32.lib")
#		pragma comment(lib, "winmm.lib")
#else

#endif

class GDesktop
{
	public:
		/* OK WIN */	static void		HideIcons(void);
		/* OK WIN */	static void		ShowIcons(void);
		/* OK WIN */	static void		ChangeIconsStyle(void);
};

#endif
