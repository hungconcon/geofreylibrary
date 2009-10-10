using System;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace G
{
    public class GSystem
    {

        [DllImport("winmm.dll")]
        public static extern long mciSendString(string lptstrcommand, string lptreturnstring, int ureturnlenght, int hwndcallback);


        public static void Reboot()
        {
            System.Diagnostics.Process.Start("shutdown", "-r -f -t 0");
        }

        public static void Shutdown()
        {
            System.Diagnostics.Process.Start("shutdown", "-s -f -t 0");
        }

        public static void LogOff()
        {
            System.Diagnostics.Process.Start("shutdown", "-l");
        }

        public static GString GetUserName()
        {
            return (new GString(Environment.UserName));
        }

        public static GString GetComputerName()
        {
            return (new GString(Environment.MachineName));
        }

        public static void Open(GString Drive)
        {
            mciSendString("open " + Drive.ToString() + ":\\ type cdaudio alias cdaudio", "", 0, 0);
            mciSendString("Set cdaudio door open wait", "", 0, 0);
            mciSendString("close cdaudio", "", 0, 0);
        }
        public static void Close(GString Drive)
        {
            mciSendString("open " + Drive.ToString() + ":\\ type cdaudio alias cdaudio", "", 0, 0);
            mciSendString("Set cdaudio door closed wait", "", 0, 0);
            mciSendString("close cdaudio", "", 0, 0);
        }


        public static GVector<GVolumeInformations>	GetVolumes()
        {
            GVector<GVolumeInformations> list = new GVector<GVolumeInformations>();
            String[] drives = Environment.GetLogicalDrives();
            UInt32 i = 0;
            while (i < drives.Length)
            {
                GVolumeInformations t = new GVolumeInformations(drives[i]);
                list.PushBack(t);
                ++i;
            }
            return (list);
         }

        public static GVector<GProcessus> GetProcessus()
        {
            System.Diagnostics.Process[] prc = Process.GetProcesses();
            UInt32 i = 0;
            GVector<GProcessus> list = new GVector<GProcessus>();
            while (i < prc.Length)
            {
                GProcessus p = new GProcessus(prc[i]);
                list.PushBack(p);
                ++i;
            }
            return (list);
        }
    }
}
