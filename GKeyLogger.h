
#ifndef __GKEYLOGGER_H__
# define __GKEYLOGGER_H__

#include "GString.h"
#include "GDate.h"
#include "GFile.h"
#include "GThread.h"
#include "GMap.hpp"
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
		void	SetPrefix(const GString &Prefix);
		void	Desactivate(void);
		bool	IsActivated(void) const;
		void	GetPath(void) const;
		void	Start(void);

	private:
		bool			_activate;
		GThread			_thread;
};

#endif
