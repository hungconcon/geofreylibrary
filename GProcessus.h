
#ifndef __GPROCESSUS_H__
# define __GPROCESSUS_H__

#include "GString.h"
#include "GExport.h"
#if defined (GWIN)
#include <tlhelp32.h>
#		include "windows.h"
#else
#		include <stdlib.h>
#		include <sys/types.h>
#		include <signal.h>
#		include <dirent.h>
#endif

class GEXPORTED GProcessus
{
public:
		GProcessus(unsigned int PID, const GString &Path);
		~GProcessus(void);

		GString				GetPath(void) const;
		unsigned int		GetPID(void) const;
		bool				Kill(void) const;
		static bool			Run(const GString &Process);
		static bool			Kill(const GString &Process);

	private:
		GString			_path;
		unsigned int	_pid;
};

#endif
