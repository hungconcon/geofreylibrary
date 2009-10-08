
#ifndef __GINTERNET_H__
# define __GINTERNET_H__

#if defined (WIN32) | defined (_WIN32) |  defined (__WIN32) | defined (WIN) | defined (WIN64) | defined (__WIN64)
#		include "windows.h"
#		include "Wininet.h"
#pragma comment(lib, "Wininet.lib")
#endif

class GInternet
{
	public:
		static bool		IsConnected(void);		
};

#endif

