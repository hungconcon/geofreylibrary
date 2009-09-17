
#ifndef __GPROCESSUS_H__
# define __GPROCESSUS_H__

#include "GString.h"
#include "GExport.h"
#if defined (GWIN)
#include <tlhelp32.h>
#		include "windows.h"
#else

#endif

class GEXPORTED GProcessus
{
public:
		GProcessus(unsigned int PID, const GString &Path);
		~GProcessus(void);

		GString			GetPath(void) const;
		unsigned int	GetPID(void) const;

		static void			Run(const GString &Process, const GString &Params = "");
		static void			Kill(const GString &Process);
		static GStringList	List(void);

	private:
		GString			_path;
		unsigned int	_pid;
};

#endif
