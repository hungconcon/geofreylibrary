
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

		bool				Mkdir(const GString &);
		bool				Rmdir(bool test = true);
		static bool			Rmdir(const GString &, bool test = true);
		static bool			Rename(const GString &, const GString &);					
		bool				Mkpath(const GString &Path);
		static bool			Rmpath(const GString &);
		static GFileList	Ls(const GString &);
		GFileList			Ls(void);
		GString				Pwd(void);
		bool				Cd(const GString &);
		bool				Exist(void);
		static bool			Exist(const GString &);
		static GString		GetPathDesktop(void);
		static GString		GetPathFonts(void);
		static GString		GetPathMusic(void);
		static GString		GetPathVideos(void);
		static GString		GetPathPictures(void);
		static GString		GetPathCookies(void);
		static GString		GetPathDocuments(void);
		static GString		GetPathHistory(void);
		static GString		GetPathStartMenu(void);
		static GString		GetPathProgramsMenu(void);
		static GString		GetPathFavorites(void);
		static GString		GetPathRoot(void);

	private:
		GString			_path;
};

#endif
