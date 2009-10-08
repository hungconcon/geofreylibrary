
#ifndef __GMOUSE_H__
# define __GMOUSE_H__

#include "GExport.h"

#if defined (GWIN)
#define OEMRESOURCE
#		include "windows.h"
#		include "winuser.h"
#endif


class GEXPORTED GMouse
{
	public:
		static void	HideCursor(void);
		static void	ShowCursor(void);
};

#endif
