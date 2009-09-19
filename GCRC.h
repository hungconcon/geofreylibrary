
#ifndef		__GCRC_H__
# define	__GCRC_H__

#include "GExport.h"
#include "GString.h"

class	GEXPORTED GCRC
{
public:
	static GString	CalculateCRC16(const GString &);
	static GString	CalculateCRC32(const GString &);
	static GString	CalculateCRC64(const GString &);
};

#endif
