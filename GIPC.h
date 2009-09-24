
#ifndef		__GIPC_H__
# define	__GIPC_H__

#include "GExport.h"
#include "GString.h"
#include "GMap.hpp"
#include "GMutex.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#if defined (GWIN)
#include <windows.h>
#else
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#endif

namespace GIPC
{

	class	GEXPORTED GPipe
	{
	public:
		GPipe(const GString &);
		void			SetName(const GString &);
		const GString	&GetName(void);
		void			SetMode(bool);
		bool			Start(void);
		bool			Read(void *, unsigned int);
		bool			Write(void *, unsigned int);
		bool			Write(const GString &);
		bool			IsReadable(void);

	private:
		bool									_read;
		GString									_name;
	#if defined	(GWIN)
		static GMap<GString, GVector<HANDLE> >	_map;
	#else
		static GMap<GString, GVector<int> >		_map;
	#endif
		static GMutex							_mutex;
	};

	class	GEXPORTED GSemaphore
	{
	public:
		GSemaphore(unsigned int, const GString & = "");
		bool	Lock(void);
		bool	Unlock(void);

	private:
		GString				_name;
		unsigned int		_nb;
#if defined	(GWIN)
		CRITICAL_SECTION	_critical;
		HANDLE				_semid; 
#else
		key_t				_key;
		int					_semid;
		unsigned int		_num;
		static unsigned int	_sum;
#endif
	};

}
#endif
