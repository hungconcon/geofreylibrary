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


struct timeval	GEXPORTED GTimeOfDay(void);
#ifdef _TIME64_T
struct timeval	GEXPORTED GTimeOfDay64(void);
#endif

#endif