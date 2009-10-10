using System;
using System.Diagnostics;

namespace G
{
    public class GProcessus
    {
        Process _proc;

        public GProcessus(Process p)
        {
            this._proc = p;
        }
        public GString GetPath()
        {
	        return (this._proc.ProcessName);
        }
        public Boolean  Kill()
        {
            Boolean test = true;
            try
            {
                this._proc.Kill();
            }
            catch
            {
                test = false;
            }
            return (test);
        }

        public static Boolean Kill(GString ProcessName)
        {
            Boolean test = true;
            try
            {
                System.Diagnostics.Process[] prc = Process.GetProcessesByName(ProcessName);
                UInt32 i = 0;
                while (i < prc.Length)
                {
                    prc[i].Kill();
                    ++i;
                }
            }
            catch
            {
                test = false;
            }
            return (test);
        }

        public static bool Run(GString ProccessName)
        {
            Boolean test = true;
            try
            {
                System.Diagnostics.Process proc = new System.Diagnostics.Process();
                proc.StartInfo.FileName = ProccessName;
                proc.Start() ;
                proc.Close();
            }
            catch
            {
                test = false;
            }
            return (test);
        }

        public static bool Run(GString ProccessName, GString Params)
        {
            Boolean test = true;
            try
            {
                System.Diagnostics.Process proc = new System.Diagnostics.Process();
                proc.StartInfo.FileName = ProccessName;
                proc.StartInfo.Arguments = Params;
                proc.Start() ;
                proc.Close();
            }
            catch
            {
                test = false;
            }
            return (test);
        }

        public UInt32   GetPID()
        {
            return ((UInt32)this._proc.Id);
        }
    }
}