
#ifndef __GSystem_H__
# define __GSystem_H__

#include "GString.h"
#include "GVector.hpp"
#include "GVolumeInformations.h"

#if defined (GWIN)
#		include <windows.h>
#else
#		include <stdlib.h>
#		include <pwd.h>
#		include <stdio.h>

#endif

class GSystem
{
	public:
						static	void						Reboot(void);
						static	void						Shutdown(void);
						static	void						LogOff(void);
						static	void						Sleep(void);
	/* OK UNIX & WIN */	static	GString						GetUserName(void);
	/* OK        WIN */	static	GString						GetComputerName(void);
	/* OK        WIN */	static	bool						SetComputerName(const GString &);
						static	void						Open(const GString &);
						static	void						Close(const GString &);
						static GVector<GVolumeInformations>	GetVolumes(void);	
						
};



#endif

