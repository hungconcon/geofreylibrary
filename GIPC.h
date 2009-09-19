
#ifndef		__GIPC_H__
# define	__GIPC_H__

#include "GExport.h"
#include "GString.h"

#include <stdio.h>

class	GEXPORTED GIPC
{
public:
	GIPC(void);
	GIPC(const GString &);

	void			SetName(const GString &);
	const GString	&GetName(void);
	bool			Open(bool Read);
	bool			Close(void);
	void			Read(void *, unsigned int);
	void			Write(void *, unsigned int);
	void			Write(const GString &);

private:
	bool					_read;
	FILE					*_fd;
	GString					_name;
};

#endif
