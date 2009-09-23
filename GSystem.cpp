
#include "GSystem.h"

void	GSystem::Reboot(void)
{
#if defined (GWIN)
	ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0);
#else

#endif
}


void	GSystem::Shutdown(void)
{
#if defined (GWIN)
	ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE,0);
#else
	GString t1("shutdown");
	char **p = new char*[2];
	p[0] = t1.ToChar();
	p[1] = NULL;
	if (execvp(p[0], p) == -1)
		GWarning::Warning("Warning - class GSystem - method Shutdown(void)\t\t=> Cannot Shutdown Computer !");
#endif
}

void	GSystem::LogOff(void)
{
#if defined (GWIN)
	ExitWindowsEx(EWX_LOGOFF | EWX_FORCE, 0);
#else

#endif
}

void	GSystem::Sleep(void)
{
#if defined (GWIN)

#else

#endif
}

GString		GSystem::GetUserName(void)
{
#if defined (GWIN)
	const unsigned long BUFSIZE = 255;
	unsigned long dwSize = BUFSIZE;
	char pbuf[BUFSIZE + 1];
	::GetUserName(pbuf, &dwSize);
	return (GString(pbuf));
#else
	register struct passwd *pw;	
	register uid_t uid;
	uid = geteuid();
	pw = getpwuid(uid);
	if (pw)
		return (GString(pw->pw_name));
	char *p = getenv("USER");
    if (p != NULL)
		return (GString(p));
	return (GString());	
#endif
}

GString		GSystem::GetComputerName(void)
{
#if defined (GWIN)
	const unsigned long BUFSIZE = 255;
	unsigned long dwSize = BUFSIZE;
	char pbuf[ BUFSIZE + 1];
	::GetComputerName(pbuf, &dwSize);
	return (GString(pbuf));
#else
	char *p = getenv("COMPUTERNAME");
    if (p != NULL)
		return (GString(p));
	return (GString(""));
#endif
}

bool		GSystem::SetComputerName(const GString &name)
{
#if defined (GWIN)
	char	*tmp = name.ToChar();
	BOOL test = ::SetComputerName(tmp);
	delete[] tmp;
	bool ReturnValue = (test != FALSE);
	return (ReturnValue);
#else
	name.ToLower();
	return (true);
#endif
}

void		GSystem::Open(const GString &Drive)
{
#if defined (GWIN)
	GString cmd = "open " + Drive + " shareable type cdaudio";
	char *c = cmd.ToChar();
	mciSendString(c, NULL, 0, NULL);
	delete [] c;
	cmd = "set " + Drive + " door open";
	c = cmd.ToChar();
	mciSendString(c, NULL, 0, NULL);
	delete c;
#elif defined(GLINUX)
	GString cmd("/etc/" + Drive);
	char *c = cmd.ToChar();
	int drive;
	drive = open(c, O_RDONLY | O_NONBLOCK);
	delete [] c;
	if (drive == -1)
		return ;
	if (ioctl(drive, CDROMEJECT) == -1)
		return ;
	if (close(drive) == -1)
		return ;
#endif
}

void		GSystem::Close(const GString &Drive)
{
#if defined (GWIN)
	GString cmd = "open " + Drive + " shareable type cdaudio";
	char *c = cmd.ToChar();
	mciSendString(c, NULL, 0, NULL);
	delete c;
	cmd = "set " + Drive + " door closed";
	c = cmd.ToChar();
	mciSendString(c, NULL, 0, NULL);
	delete c;
#elif defined(GLINUX)
	GString cmd("/etc/" + Drive);
	char *c = cmd.ToChar();
	int drive;
	drive = open(c, O_RDONLY | O_NONBLOCK);
	delete [] c;
	if (drive == -1)
		return ;
	if (ioctl(drive, CDROMCLOSETRAY) == -1)
		return ;
	if (close(drive) == -1)
		return ;
#endif
}

GVector<GVolumeInformations>	GSystem::GetVolumes(void)
{
	GVector<GVolumeInformations> list;
#if defined (GWIN)
	char buffer[1024];
	HANDLE hEnt;
	if ((hEnt = FindFirstVolume(buffer, 1024)) != INVALID_HANDLE_VALUE)
    {
        do
		{
			GVolumeInformations t(buffer);
			list.PushBack(t);
		}
        while (FindNextVolume(hEnt, buffer, 1024));   
        FindVolumeClose(hEnt);
    }
#endif
	return (list);
}

GVector<GProcessus>	GSystem::GetProcessus(void)
{
	GVector<GProcessus> list;
#if defined (GWIN)
    HANDLE hSnapShot;
    PROCESSENTRY32 pe;
    hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (Process32First(hSnapShot, &pe))
    {
        do
		{
			GProcessus t(pe.th32ProcessID, pe.szExeFile);
			list.PushBack(t);
		}
        while (Process32Next(hSnapShot, &pe));
    }
    CloseHandle(hSnapShot);
#elif defined(GUNIX) 
	struct dirent *Read;
	DIR *rep;
	rep = opendir("/proc");
	if (rep == NULL)
		return (list);
	while ((Read = readdir(rep)))
	{
		if (atoi(Read->d_name) > 0 && atoi(Read->d_name) < 32768)
		{
			char buffer[1024];
			GString s(Read->d_name);
			s = "/proc/" + s + "/file";
			int n = readlink(s.ToChar(), buffer, 1024);
			if (n != -1)
			{
				buffer[n] = 0;
				GProcessus t(atoi(Read->d_name), buffer);
				list.PushBack(t);
			}
		}
	}
	closedir(rep); 
#endif
	return (list);

}
