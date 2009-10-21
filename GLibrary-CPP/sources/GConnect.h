
#ifndef		__GCONNECT_H__
# define	__GCONNECT_H__

#include "GThread.h"
#include "GString.h"
#include "GMap.hpp"
#include "GMutex.h"
#include "GPair.hpp"
//#define SIGNAL(x)

typedef GMap<GString, GPair<GFunction, bool> >	GPointerMap;

class GConnect
{
	public:
		static void	Connect(const GString &, GFunction);
		static void	Disconnect();
		static void Disconnect(const GString &);
		//static void	Emit(const GString &);

		static void	Lock(void);
		static void Unlock(void);

	private:
		static void StopThread(void);
		static void StartThread(void);
		static void *Check(void *);
		static void	AddConnect(const GString &, GFunction);
		static void	RemoveConnect(const GString &, GFunction);
		static void	RemoveConnect(const GString &);

		static GThread		*_Thread;
		static GPointerMap	_Map;
		static GMutex		_Mutex;
};

#endif
