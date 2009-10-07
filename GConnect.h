
#ifndef __GCONNECT_H__
# define __GCONNECT_H__

#include "GThread.h"
#include "GString.h"
#include "GMap.hpp"
#include "GMutex.h"
//#define SIGNAL(x)



typedef GMap<GString, GFunction>	GPointerMap;

class GConnect
{
	public:
		static void	Connect(const GString &, GFunction);
		static void	Disconnect();

		static void	Lock(void);
		static void Unlock(void);

	private:
		static void StopThread(void);
		static void StartThread(void);
		static void *Check(void *);

		static GThread		*Thread;
		static GPointerMap	*Map;
		static GMutex		*Mutex;
};

#endif