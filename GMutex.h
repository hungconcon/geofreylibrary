
#ifndef __GMUTEX_H__
# define __GMUTEX_H__

#include "GExport.h"

#if defined (GWIN)
#		include <windows.h>
#		include "Winbase.h"
#else
#		include <pthread.h>
#endif

class GEXPORTED GMutex
{
	public:
		GMutex(void);
		~GMutex(void);
	
		void	Lock(void);
		void	TryLock(void);
		void	Unlock(void);
		bool	IsLock(void) const;

	private:
		#if defined (GWIN)
			HANDLE				_mutex;
			CRITICAL_SECTION	_cr_sct;
		#else
			pthread_mutex_t _mutex;
		#endif
		bool	_lock;
};


#endif

