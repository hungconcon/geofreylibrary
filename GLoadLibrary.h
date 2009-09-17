
#ifndef __GLOADLIBRARY_H__
# define __GLOADLIBRARY_H__

#include "GMap.hpp"
#include "GString.h"
#include "GFileInfos.h"
#include "GDirectory.h"
#include "GExport.h"

#if defined (GWIN)
#		include "windows.h"	
typedef HINSTANCE	GLibrary; 
#else
#		include <sys/types.h>
#		include <dirent.h>
#		include <dlfcn.h>
typedef void *		GLibrary; 
#endif
typedef void *		GMethod;

class GEXPORTED GLoadLibrary
{
	public:
		GLoadLibrary(void);
		GLoadLibrary(const GString &Directory);
		~GLoadLibrary(void);

		bool			LdLibrary(const GString &Library);
		void			LoadAllLibrary(void);
		GLibrary		GetLibrary(const GString &Library);
		GMethod			GetFunction(const GString &Library, const GString &Method);
		static GMethod	GetFunction(GLibrary Library, const GString &Method);
		void			UnloadLibrary(const GString &Library);
		void			SetDirectory(const GString &Directory);

	private:
		typedef	GMap<GString, GLibrary>	GLibraryMap;
		GLibraryMap	_map;
		GString		_directory;
		bool		_test;
};

#endif



