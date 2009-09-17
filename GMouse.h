
#ifndef __GMOUSE_H__
# define __GMOUSE_H__

#if defined (GWIN)
#		include "windows.h"
#		include "winuser.h"
#		define OCR_APPSTARTING 32650
#		define OCR_NORMAL 32512

#else

#endif


class GMouse
{
	public:
		static void	HideCursor(void);
};

#endif
