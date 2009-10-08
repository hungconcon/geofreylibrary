#include "GStr.h"

void	GStrcpy(char *dest, char *source)
{
	unsigned int i = 0;
	while (source[i])
	{
		dest[i] = source[i];
		++i;
	}
	dest[i] = 0;
}
void	GStrcpy(char *dest, char *source, unsigned int Size)
{
	unsigned int i = 0;
	while (i < Size)
	{
		dest[i] = source[i];
		++i;
	}
}
unsigned int GStrlen(char *Str)
{
	unsigned int i = 0;
	while (Str[i])
		++i;
	return (i);
}
