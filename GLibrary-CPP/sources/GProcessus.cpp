
#include "GProcessus.h"

GProcessus::GProcessus(unsigned int PID, const GString &Path)
{
	this->_pid = PID;
	this->_path = Path;
}

GProcessus::~GProcessus(void)
{
	
}

GString		GProcessus::GetPath(void) const
{
	return (this->_path);
}

unsigned int GProcessus::GetPID(void) const
{
	return (this->_pid);
}

bool	GProcessus::Kill(void) const
{
#if defined(GWIN)
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, this->_pid);
	if (hProcess == NULL)
		return (false);
	if (TerminateProcess(hProcess, 0) == 0)
		return (false);
	CloseHandle(hProcess);
#else
	if (kill(this->_pid, SIGKILL) == -1)
		return (false);
#endif
	return (true);
}

bool	GProcessus::Kill(const GString &Process)
{
#if defined(GWIN)
    HANDLE hSnapShot;
    PROCESSENTRY32 pe;
    hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapShot == INVALID_HANDLE_VALUE)
		return (false);
	if (Process32First(hSnapShot, &pe))
    {
        do
		{
			GString s(pe.szExeFile);
			if (s == Process)
			{
				HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
				if (hProcess == NULL)
					return (false);
				if (TerminateProcess(hProcess, 0) == 0)
					return (false);
				CloseHandle(hProcess);	
			}
		}
        while (Process32Next(hSnapShot, &pe));
    }
    CloseHandle(hSnapShot);
#elif defined(GUNIX)
	struct dirent *Read;
	DIR *rep;
	rep = opendir("/proc");
	if (rep == NULL)
		return (false);
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
				if (GString(buffer) == Process)
				{
					if (kill(atoi(Read->d_name), SIGKILL) == -1)
						return (false);
				}
			}
		}
	}
	closedir(rep); 

#endif
	return (true);
}

bool	GProcessus::Run(const GString &name)
{
#if defined(GWIN)
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&si, sizeof(STARTUPINFO));
	if (CreateProcess(name.ToLPCSTR(), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, (LPSTARTUPINFO) &si, (LPPROCESS_INFORMATION) &pi) == 0)
		return (false);
#elif defined(GUNIX)
	char *tab;
	tab = name.ToChar();
	if (system(tab) == -1)
	{
		delete tab;
		return (false);
	}
	delete tab;
#endif
	return (true);
}


