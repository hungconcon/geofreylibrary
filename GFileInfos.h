
#ifndef __GFILEINFOS_H__
# define __GFILEINFOS_H__

#include "GString.h"
#include "GDateTime.h"
#include "GExport.h"

#if defined (GUNIX)
#		include <sys/types.h>
#		include <sys/stat.h>
#endif


class GEXPORTED GFileInfos
{
	public:
		GFileInfos(void);
		GFileInfos(const GString &);
		GFileInfos(const GString &, const GString &);
		
		bool			Exist(void);

		static GString	FileName(const GString &);
		static bool		IsDir(const GString &);

		GString			FileName(void) const;
		bool			IsDir(void);


		long long		Size(void) const;
		GString			FormatedSize(unsigned int = 1) const;
		bool			IsDir(void) const;
		
		
		GDateTime		BirthTime(void) const;
		GDateTime		LastModificationTime(void) const;
		GDateTime		LastAccessTime(void) const;
		
		void			SetFile(const GString &);

	private:
		GString		_file;
		#if defined (GWIN)
			WIN32_FILE_ATTRIBUTE_DATA	_stat;
		#else
			struct stat		_stat;
		#endif
};

#endif
