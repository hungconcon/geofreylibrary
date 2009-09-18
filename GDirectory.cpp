
#include "GDirectory.h"

GDirectory::GDirectory(void)
{
	this->Cd(".");
}

GDirectory::~GDirectory(void)
{

}

bool	GDirectory::Exist(void)
{
	char	*tmp = this->_path.ToChar();
	bool	ok(true);
#if defined (GWIN)
	if (GetFileAttributes(tmp) == INVALID_FILE_ATTRIBUTES)
		ok = (false);
#else
	struct stat s;
	if (lstat(tmp, &s) == -1)
		ok = (false);
#endif
	delete[] tmp;
	return (ok);
}

bool	GDirectory::Exist(const GString &Path)
{
	char	*tmp = Path.ToChar();
	bool	ok(true);
#if defined (GWIN)
	if (GetFileAttributes(tmp) == INVALID_FILE_ATTRIBUTES)
		ok = (false);
#else
	struct stat s;
	if (lstat(tmp, &s) == -1)
		ok = (false);
#endif
	delete[] tmp;
	return (ok);
}

GFileList	GDirectory::Ls(void)
{
	GFileList	list;
	char	*tmp;
#if defined (GWIN)
    HANDLE hEnt;
    WIN32_FIND_DATA ent;
	tmp = GString(this->_path + "/" + "*").ToChar();
	if ((hEnt = FindFirstFile(tmp, &ent)) != INVALID_HANDLE_VALUE)
    {
        do
		{
			GFileInfos t(ent.cFileName);
			list.PushBack(t);
		}
        while (FindNextFile(hEnt, &ent));   
        FindClose(hEnt);
    }
#else
	tmp = this->_path.ToChar();
	DIR * rep = opendir(tmp);
	if (rep != NULL)
	{ 
		struct dirent *ent;
		while ((ent = readdir(rep)) != NULL) 
		{ 
			GFileInfos t(ent->d_name);
			list.PushBack(t);
		}  
		closedir (rep); 
	} 
#endif
	delete[] tmp;
	return (list);
}

GFileList	GDirectory::Ls(const GString &p)
{
	GFileList	list;
	char	*tmp;
#if defined (GWIN)
    HANDLE hEnt;
    WIN32_FIND_DATA ent;
	tmp = GString(p+ "/" + "*").ToChar();
	if ((hEnt = FindFirstFile(tmp, &ent)) != INVALID_HANDLE_VALUE)
    {
        do
		{
			GFileInfos t(ent.cFileName);
			list.PushBack(t);
		}
        while (FindNextFile(hEnt, &ent));   
        FindClose(hEnt);
    }
#else
	tmp = p.ToChar();
	DIR * rep = opendir(tmp);
	if (rep != NULL)
	{ 
		struct dirent *ent;
		while ((ent = readdir(rep)) != NULL) 
		{ 
			GFileInfos t(ent->d_name);
			list.PushBack(t);
		}  
		closedir (rep); 
	}
#endif
	delete[] tmp;
	return (list);
}

bool		GDirectory::Mkdir(const GString &s)
{
	char	*tmp = s.ToChar();
	bool	ok(true);
#if defined (GWIN)
	if (CreateDirectory(tmp, NULL) == 0)
		ok = (false);
#else
	if (mkdir(tmp, NULL) == -1)
		ok = (false);
#endif
	delete[] tmp;
	return (ok);
}

bool		GDirectory::Mkpath(const GString &s)
{
	GString current = this->Pwd();
	GStringList list = s.Split("\\");
	for (unsigned int i = 0; i < list.Size(); ++i)
	{
		char	*tmp = list[i].ToChar();
#if defined (GWIN)
		if (CreateDirectory(tmp, NULL) == 0)
#else
		if (mkdir(tmp, NULL) == -1)
#endif
		{
			delete[] tmp;
			this->Cd(current);
			return (false);
		}
		delete[] tmp;
		this->Cd(list[i]);
	}
	this->Cd(current);
	return (true);
}

bool		GDirectory::Rename(const GString &f1, const GString &f2)
{
	bool	ok(true);
#if defined (GWIN)
	char	*tmp1 = f1.ToChar();
	char	*tmp2 = f2.ToChar();
	if (MoveFile(tmp1, tmp2) == 0)
		ok = (false);
	delete[] tmp1;
	delete[] tmp2;
#else

#endif
	return (ok);
}

GString		GDirectory::Pwd(void)
{
#if defined (GWIN)
	TCHAR szPath[1024]; 
	int n;
	if ((n = GetCurrentDirectory(1024, szPath)) == 0)
		throw GException(G::CANNOT_GET_CURRENT_PATH);
	if (n == 0)
		return (this->_path);
	this->_path = GString(szPath);
#else
	char *path = new char[1024];
	if (getwd(path) == NULL)
		throw GException(G::CANNOT_GET_CURRENT_PATH);
	this->_path = path;
	delete[] path;
#endif
	return (this->_path);
}

bool	GDirectory::Cd(const GString &d)
{
	char	*tmp = d.ToChar();
	bool	ok(true);
#if defined (GWIN)
	if (SetCurrentDirectory(tmp) == 0)
		ok = false;
#else
	if (chdir(tmp) == -1)
		ok = false;
#endif
	delete[] tmp;
	this->Pwd();
	return (ok);
}

bool		GDirectory::Rmdir(bool test)
{
	if (test == true)
	{
		GFileList content = GDirectory::Ls(this->_path);
		for (unsigned int i = 0; i < content.Size(); i++)
		{
			if (content[i].FileName() != "." && content[i].FileName() != "..")
			{
				if (content[i].IsDir())
					GDirectory::Rmdir(this->_path + "/" + content[i].FileName());
				else
					GFile::Rm(this->_path + "/" + content[i].FileName());
			}
		}
	}
	char	*tmp = this->_path.ToChar();
	bool	ok(true);
#if defined (GWIN)
	if (RemoveDirectory(tmp) == 0)
		ok = (false);
#else
	if (rmdir(tmp) == -1)
		ok = (false);
#endif
	delete[] tmp;
	return (ok);
}

bool		GDirectory::Rmdir(const GString &d, bool test)
{
	if (test == true)
	{
		GFileList content = GDirectory::Ls(d);
		for (unsigned int i = 0; i < content.Size(); i++)
		{
			if (content[i].FileName() != "." && content[i].FileName() != "..")
			{
				if (content[i].IsDir())
					GDirectory::Rmdir(d + "/" + content[i].FileName());
				else
					GFile::Rm(d + "/" + content[i].FileName());
			}
		}
	}
	char	*tmp = d.ToChar();
	bool	ok(true);
#if defined (GWIN)
	if (RemoveDirectory(tmp) == 0)
		ok = (false);
#else
	if (rmdir(tmp) == -1)
		ok = (false);
#endif
	delete[] tmp;
	return (ok);
}


bool		GDirectory::Rmpath(const GString &)
{
	return (true);	
}

GString		GDirectory::GetPathDesktop(void)
{
#if defined (GWIN)
	GRegistry r;
	r.OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
	GString t(r.ReadStringValue("Desktop"));
	r.CloseKey();
	return (t);
#else
	return ("");
#endif
}

GString		GDirectory::GetPathFonts(void)
{
#if defined (GWIN)
	GRegistry r;
	r.OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
	GString t(r.ReadStringValue("Fonts"));
	r.CloseKey();
	return (t);
#else
	return ("");
#endif
}

GString		GDirectory::GetPathMusic(void)
{
#if defined (GWIN)
	GRegistry r;
	r.OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
	GString t(r.ReadStringValue("My Music"));
	r.CloseKey();
	return (t);
#else
	return ("");
#endif
}
GString		GDirectory::GetPathVideos(void)
{
#if defined (GWIN)
	GRegistry r;
	r.OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
	GString t(r.ReadStringValue("My Video"));
	r.CloseKey();
	return (t);
#else
	return ("");
#endif
}
GString		GDirectory::GetPathPictures(void)
{
#if defined (GWIN)
	GRegistry r;
	r.OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
	GString t(r.ReadStringValue("My Pictures"));
	r.CloseKey();
	return (t);
#else
	return ("");
#endif
}
GString		GDirectory::GetPathCookies(void)
{
#if defined (GWIN)
	GRegistry r;
	r.OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
	GString t(r.ReadStringValue("Cookies"));
	r.CloseKey();
	return (t);
#else
	return ("");
#endif
}
GString		GDirectory::GetPathDocuments(void)
{
#if defined (GWIN)
	GRegistry r;
	r.OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
	GString t(r.ReadStringValue("Personal"));
	r.CloseKey();
	return (t);
#else
	return ("");
#endif
}
GString		GDirectory::GetPathHistory(void)
{
#if defined (GWIN)
	GRegistry r;
	r.OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
	GString t(r.ReadStringValue("History"));
	r.CloseKey();
	return (t);
#else
	return ("");
#endif
}
GString		GDirectory::GetPathStartMenu(void)
{
#if defined (GWIN)
	GRegistry r;
	r.OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
	GString t(r.ReadStringValue("Start Menu"));
	r.CloseKey();
	return (t);
#else
	return ("");
#endif
}
GString		GDirectory::GetPathProgramsMenu(void)
{
#if defined (GWIN)
	GRegistry r;
	r.OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
	GString t(r.ReadStringValue("Programs"));
	r.CloseKey();
	return (t);
#else
	return ("");
#endif
}
GString		GDirectory::GetPathFavorites(void)
{
#if defined (GWIN)
	GRegistry r;
	r.OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
	GString t(r.ReadStringValue("Favorites"));
	r.CloseKey();
	return (t);
#else
	return ("");
#endif
}
GString		GDirectory::GetPathRoot(void)
{
#if defined (GWIN)
	const unsigned long BUFSIZE = 255;
	unsigned long dwSize = BUFSIZE;
	char pbuf[ BUFSIZE + 1];
	::GetWindowsDirectory(pbuf, dwSize);
	return (pbuf);
#else
	return ("");
#endif
}



/*
#  m_AppData = m_Reg.LireStr("AppData");
# m_Cache = m_Reg.LireStr("Cache");
# m_LocalAppData = m_Reg.LireStr("Local AppData");
# m_LocalSettings = m_Reg.LireStr("Local Settings");
# m_VoisinageReseau = m_Reg.LireStr("NetHood");
# m_VoisinageImpression = m_Reg.LireStr("PrintHood");
# m_Recents = m_Reg.LireStr("Recent");
# m_EnvoyerVers = m_Reg.LireStr("SendTo");
# m_Demarrage = m_Reg.LireStr("Startup");
# m_Modeles = m_Reg.LireStr("Templates");

*/
