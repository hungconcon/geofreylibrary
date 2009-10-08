
#if defined (WIN32) | defined (_WIN32) |  defined (__WIN32) | defined (WIN) | defined (WIN64) | defined (__WIN64)
#	include <windows.h>
#endif
#include "GSleep.h"


void GSleep(unsigned int time)
{
#if defined (WIN32) | defined (_WIN32) |  defined (__WIN32) | defined (WIN) | defined (WIN64) | defined (__WIN64)
	Sleep(time * 1000);
#else
	sleep(time);
#endif
}

void GUSleep(unsigned int time)
{
#if defined (WIN32) | defined (_WIN32) |  defined (__WIN32) | defined (WIN) | defined (WIN64) | defined (__WIN64)
	Sleep(time);
#else
	usleep(time);
#endif
}




