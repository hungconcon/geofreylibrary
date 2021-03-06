
#include "GTimeOfDay.h"

struct timeval	GTimeOfDay(void)
{
	struct timeval tv;
#if defined(GWIN)
	struct __timeb64 timebuffer;
	_ftime64_s(&timebuffer);
	tv.tv_sec = (long)timebuffer.time;
	tv.tv_usec = timebuffer.millitm * 1000;
#else
	gettimeofday(&tv, NULL);
#endif
	return (tv);
}

struct timeval64	GTimeOfDay64(void)
{
	struct timeval64 tv;
#if defined(GWIN)
	struct __timeb64 timebuffer;
	_ftime64_s(&timebuffer);
	tv.tv_sec = timebuffer.time;
	tv.tv_usec = timebuffer.millitm * 1000;
#else
	//gettimeofday(&tv, NULL);
#endif
	return (tv);
}
