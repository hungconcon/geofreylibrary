
#ifndef		__GRANDOM_H__
# define	__GRANDOM_H__

#include "GExport.h"
#include <stdlib.h>

#if defined (GWIN)
#		include <windows.h>
#		include <time.h>
#		include <sys/timeb.h>
#else
#		include <sys/time.h>
#endif

unsigned int	GEXPORTED GRandom(void);
unsigned int	GEXPORTED GRandom(unsigned int min, unsigned int max);

#endif
