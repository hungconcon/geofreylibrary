
#ifndef		__GMUSIC_H__
# define	__GMUSIC_H__

#include "GExport.h"
#include "GString.h"

#if defined (GWIN)
#		include <windows.h>
#		include <tlhelp32.h>
#pragma comment(lib, "winmm.lib")
#else
#		include <stdlib.h>
#		include <pwd.h>
#		include <dirent.h>
#		include <stdio.h>

#endif

class	GEXPORTED GMusic
{
public:
	GMusic(void);
	GMusic(const GMusic &Music);
	GMusic(const GString &MusicPath);
	~GMusic(void);
	void	SetMusic(const GString &MusicPath);
	bool	Play(void);
	bool	Pause(void);
	bool	Stop(void);
	bool	IsPlayed(void) const;

private:
	GString			_file;
	bool			_playing;
#if defined (GWIN)
	MCI_OPEN_PARMS	OpenParam;
#endif
};

#endif

