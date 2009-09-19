
#ifndef		__GIPC_H__
# define	__GIPC_H__

#include "GExport.h"
#include "GString.h"
#include "GMap.hpp"
#include "GMutex.h"

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#if defined (GWIN)
#include <windows.h>
#else
#include <unistd.h>
#endif

class	GEXPORTED GIPC
{
public:
	GIPC(const GString &);
	void			SetName(const GString &);
	const GString	&GetName(void);
	void			SetMode(bool);
	bool			Start(void);
	bool			Read(void *, unsigned int);
	bool			Write(void *, unsigned int);
	bool			Write(const GString &);
	bool			IsReadable(void);

private:
	bool									_read;
	GString									_name;
#if defined	(GWIN)
	static GMap<GString, GVector<HANDLE> >	_map;
#else
	static GMap<GString, GVector<int> >		_map;
#endif
	static GMutex							_mutex;
};

#endif
