
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

void	GProcessus::Kill(void) const
{
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, this->_pid);
	TerminateProcess(hProcess, 0);
	CloseHandle(hProcess);
}

void	GProcessus::Kill(const GString &Process)
{
    HANDLE hSnapShot;
    PROCESSENTRY32 pe;
    hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (Process32First(hSnapShot, &pe))
    {
        do
		{
			GString s(pe.szExeFile);
			if (s == Process)
			{
				HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
				TerminateProcess(hProcess, 0);
				CloseHandle(hProcess);	
			}
		}
        while (Process32Next(hSnapShot, &pe));
    }
    CloseHandle(hSnapShot);
}

void	GProcessus::Run(const GString &name)
{
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&si, sizeof(STARTUPINFO));
	CreateProcess(name.ToLPCSTR(), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, (LPSTARTUPINFO) &si, (LPPROCESS_INFORMATION) &pi);
}


