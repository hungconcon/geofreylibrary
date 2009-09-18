#ifndef __GTHREAD_H__
# define __GTHREAD_H__

#include <iostream>
#include "GExport.h"
#if defined (GWIN)
#		include <windows.h>
#		include "Winbase.h"
typedef DWORD	GThreadId;
typedef HANDLE	GThreadUnit;
#else
#		include <pthread.h>
typedef pthread_t	GThreadUnit;
typedef int			GThreadId;
#endif

typedef void	*(*GFunction)(void *);
typedef void	*(*GFunction_void_void)(void);

class GEXPORTED GThread
{
	public:
		GThread(void);
		GThread(GFunction);
		~GThread(void);

		void		Abort(void);
		void		Start(void *arg);
		void		Start(void);
		void		SetFunction(GFunction);
		GThreadId	GetId(void) const;

	private:
		GThreadUnit		_thread;
		GFunction		_function;
		GThreadId		_id;
		bool			_set;
		bool			_start;
};

#endif

