using System;
using System.Runtime.InteropServices;

namespace G
{
    public class GSystem
    {

        [DllImport("winmm.dll")]
        public static extern long mciSendString(string lptstrcommand, string lptreturnstring, int ureturnlenght, int hwndcallback);


        public void Reboot()
        {
            ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0);
        }

        public void Shutdown()
        {
            ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0);
        }

        public void LogOff()
        {
            ExitWindowsEx(EWX_LOGOFF | EWX_FORCE, 0);
        }

        public GString GetUserName()
        {
            return (new GString(Environment.UserName));
        }

        public GString GetComputerName()
        {
            return (new GString(Environment.MachineName));
        }

        public void Open(GString Drive)
        {
            mciSendString("open " + Drive.ToString() + ":\\ type cdaudio alias cdaudio", "", 0, 0);
            mciSendString("Set cdaudio door open wait", "", 0, 0);
            mciSendString("close cdaudio", "", 0, 0);
        }
        public void Close(GString Drive)
        {
            mciSendString("open " + Drive.ToString() + ":\\ type cdaudio alias cdaudio", "", 0, 0);
            mciSendString("Set cdaudio door closed wait", "", 0, 0);
            mciSendString("close cdaudio", "", 0, 0);
        }


        /*GVector<GVolumeInformations>	GSystem::GetVolumes(void)
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
                */
    }
}
