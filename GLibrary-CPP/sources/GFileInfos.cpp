
#include "GFileInfos.h"
#include "GMessageBox.h"

#include <iostream>

GFileInfos::GFileInfos(void)
{
	
}

GFileInfos::GFileInfos(const GString &f)
{
	this->_file = f;
	#if defined (GWIN)
	if (!GetFileAttributesEx(this->_file.ToChar(), GetFileExInfoStandard, &this->_stat))
		GWarning::Warning("GFileInfos", "GFileInfos(const GString &)", "Cannot get struct WIN32_FILE_ATTRIBUTE_DATA !");
	#else
		if (lstat(this->_file.ToChar(), &this->_stat) == -1)
			GWarning::Warning("GFileInfos", "GFileInfos(const GString &)", "Cannot get struct stat !");
	#endif
}

GFileInfos::GFileInfos(const GString &, const GString &)
{
	
}

GString			GFileInfos::FileName(void) const
{
#if defined (GWIN)
	return (this->_file);
#else
	return (this->_file);
#endif
}

bool			GFileInfos::IsDir(const GString &s)
{
#if defined (GWIN)
	if ((GetFileAttributes(s.ToLPCSTR()) & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) 
		return (true);
    return (false);
#else
	struct stat st;
	if (lstat(s.ToChar(), &st) == -1)
			GWarning::Warning("GFileInfos", "GFileInfos(const GString &)", "Cannot get struct stat !");
	if ((st.st_mode & S_IFDIR) != 0)
		return (true);
	return (false);
#endif
}

bool			GFileInfos::IsDir(void)
{
#if defined (GWIN)
	if ((GetFileAttributes(this->_file.ToLPCSTR()) & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) 
		return (true);
    return (false);
#else
	if ((this->_stat.st_mode & S_IFDIR) != 0)
		return (true);
	return (false);
#endif
}


void			GFileInfos::SetFile(const GString &f)
{
	this->_file = f;
	#if defined (GWIN)
	if (!GetFileAttributesEx(this->_file.ToChar(), GetFileExInfoStandard, &this->_stat))
		GWarning::Warning("GFileInfos", "GFileInfos(const GString &)", "Cannot get struct WIN32_FILE_ATTRIBUTE_DATA !");
	#else
		if (lstat(this->_file.ToChar(), &this->_stat) == -1)
			GWarning::Warning("GFileInfos", "GFileInfos(const GString &)", "Cannot get struct stat !");
	#endif
}

long long	GFileInfos::Size(void) const
{
	#if defined (GWIN)
		long long size((this->_stat.nFileSizeHigh * MAXDWORD));
		if (this->_stat.nFileSizeHigh > 1)
			size *= 2;
		size += this->_stat.nFileSizeLow;
		return (size);
	#else
		return (this->_stat.st_size);
	#endif
}

GString			GFileInfos::FormatedSize(unsigned int num) const
{
	long long	size(this->Size());
	GStringList name;
	name.PushBack("k");
	name.PushBack("M");
	name.PushBack("G");
	unsigned int j  = 0;
	long long newsize(size / 1024);
	if (newsize == 0)
		return ("1.0");
	while (newsize > 1024)
	{
		newsize /= 1024;
		j++;
	}
	return (GString(newsize, num) + name[j]);
}

GDateTime		GFileInfos::BirthTime(void) const
{
#if defined (GWIN)
	SYSTEMTIME St;
	FILETIME t;
	FileTimeToLocalFileTime(&this->_stat.ftCreationTime, &t);
	FileTimeToSystemTime(&t, &St);
	return (GDateTime(St.wYear, St.wMonth - 1, St.wDay, St.wHour, St.wMinute, St.wSecond));	
#elif defined(GBSD)
	struct tm *s = new (struct tm);
	s = gmtime(&(this->_stat.st_birthtime));
	GDateTime d(s->tm_year, s->tm_mon, s->tm_mday, s->tm_hour, s->tm_min, s->tm_sec);
	delete s;
	return (d);
#endif
}

GDateTime	GFileInfos::LastModificationTime(void) const
{
#if defined (GWIN)
	SYSTEMTIME St;
	FILETIME t;
	FileTimeToLocalFileTime(&this->_stat.ftLastWriteTime, &t);
	FileTimeToSystemTime(&t, &St);
	return (GDateTime(St.wYear, St.wMonth - 1, St.wDay, St.wHour, St.wMinute, St.wSecond));	
#else
	struct tm *s = new (struct tm);
	s = gmtime(&(this->_stat.st_mtime));
	GDateTime *d = new GDateTime(s->tm_year, s->tm_mon, s->tm_mday, s->tm_hour, s->tm_min, s->tm_sec);
	return (*d);
#endif
}
GDateTime	GFileInfos::LastAccessTime(void) const
{
#if defined (GWIN)
	SYSTEMTIME St;
	FILETIME t;
	FileTimeToLocalFileTime(&this->_stat.ftLastAccessTime, &t);
	FileTimeToSystemTime(&t, &St);
	return (GDateTime(St.wYear, St.wMonth - 1, St.wDay, St.wHour, St.wMinute, St.wSecond));
#else
	struct tm *s = new (struct tm);
	s = gmtime(&(this->_stat.st_atime));
	GDateTime *d = new GDateTime(s->tm_year, s->tm_mon, s->tm_mday, s->tm_hour, s->tm_min, s->tm_sec);
	return (*d);
#endif
}

bool	GFileInfos::Exist(void)
{
#if defined (GWIN)
	if (GetFileAttributes(this->_file.ToLPCSTR()) == INVALID_FILE_ATTRIBUTES)
		return (false);
#else
	if (lstat(this->_file.ToChar(), &this->_stat) == -1)
		return (false);
#endif
	return (true);
}

