
#ifndef __GDIRECTORY_H__
# define __GDIRECTORY_H__

#include "GString.h"
#include "GException.h"
#include "GFileInfos.h"
#include "GFile.h"
#include "GExport.h"
typedef GVector<GFileInfos> GFileList;


#if defined (GWIN)
#		include	"GRegistry.h"
#else
#		include <sys/types.h>
#		include <sys/stat.h>
#		include <unistd.h>
#		include <errno.h>
#		include <dirent.h>
#endif


class GEXPORTED GDirectory
{
	public:
		GDirectory(void);
		~GDirectory(void);

		/* OK UNIX & WIN */ bool				Mkdir(const GString &);
		/* OK UNIX & WIN */	bool				Rmdir(bool test = true);
		/* OK UNIX & WIN */ static bool			Rmdir(const GString &, bool test = true);
		/* OK      & WIN */ static bool			Rename(const GString &, const GString &);					
							bool				Mkpath(const GString &Path);
							static bool			Rmpath(const GString &);
							static GFileList	Ls(const GString &);
							GFileList			Ls(void);
		/* OK UNIX & WIN */	GString				Pwd(void);
		/* OK UNIX & WIN */	bool				Cd(const GString &);
							bool				Exist(void);
							static bool			Exist(const GString &);
		/* OK        WIN */	static GString		GetPathDesktop(void);
		/* OK        WIN */	static GString		GetPathFonts(void);
		/* OK        WIN */	static GString		GetPathMusic(void);
		/* OK        WIN */	static GString		GetPathVideos(void);
		/* OK        WIN */	static GString		GetPathPictures(void);
		/* OK        WIN */	static GString		GetPathCookies(void);
		/* OK        WIN */	static GString		GetPathDocuments(void);
		/* OK        WIN */	static GString		GetPathHistory(void);
		/* OK        WIN */	static GString		GetPathStartMenu(void);
		/* OK        WIN */	static GString		GetPathProgramsMenu(void);
		/* OK        WIN */	static GString		GetPathFavorites(void);
		/* OK        WIN */	static GString		GetPathRoot(void);

	private:
		GString			_path;
};

#endif
