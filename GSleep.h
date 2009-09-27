
#ifndef __GSLEEP_H__
# define __GSLEEP_H__

#include "GExport.h"

#if defined (GWIN)
#else
#include <unistd.h>
#endif

void GEXPORTED GSleep(unsigned int Seconds);
void GEXPORTED GUSleep(unsigned int MicroSeconds);

#endif
