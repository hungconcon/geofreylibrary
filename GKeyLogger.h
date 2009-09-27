
#ifndef __GKEYLOGGER_H__
# define __GKEYLOGGER_H__

#include "GString.h"
#include "GDateTime.h"
#include "GFile.h"
#include "GThread.h"
#include "GMap.hpp"
#include "GMutex.h"

#if defined (GWIN)
#		include "windows.h"
#endif

class GKeyLogger
{
	public:
		GKeyLogger(void);
		~GKeyLogger(void);

		void	Activate(void);
		void	SetDirectory(const GString &Directory);
		void	SetFileName(const GString &Prefix);
		void	Desactivate(void);
		bool	IsActivated(void) const;
		void	GetPath(void) const;
		void	Start(void);

	private:
		bool			_activate;
		GThread			_thread;
		GMutex			_mutex;
};

#endif
