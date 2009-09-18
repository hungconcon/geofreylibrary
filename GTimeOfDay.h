#ifndef	__GTIMEOFDAY_H__
# define __GTIMEOFDAY_H__

#include "GExport.h"

#if defined (GWIN)
#		include <windows.h>
#		include <time.h>
#		include <sys/timeb.h>
#else
#		include <sys/time.h>
#endif

#ifndef _TIME64_T
struct timeval64
{
	long long	tv_sec;
	int			tv_usec;
};
#endif

struct timeval		GEXPORTED GTimeOfDay(void);
struct timeval64	GEXPORTED GTimeOfDay64(void);

#endif