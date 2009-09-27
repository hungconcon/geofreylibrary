
#ifndef __GSTR_H__
# define __GSTR_H__

#include <iostream>
#include "GExport.h"

void			GEXPORTED GStrcpy(char *Dest, char *Source);
void			GEXPORTED GStrcpy(char *Dest, char *Source, unsigned int Size);
unsigned int	GEXPORTED GStrlen(char *Str);
#endif
