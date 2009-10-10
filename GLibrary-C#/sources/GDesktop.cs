using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace G
{
    public class GDesktop
    {
        private static Int32 SW_HIDE = 0;
        private static Int32 SW_SHOW = 5;

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        public static extern IntPtr FindWindow(string strClassName, string strWindowName);

        [DllImport("User32")] 
        private static extern int ShowWindow(IntPtr hwnd, int nCmdShow);

        public static void      HideIcons()
        {
 	        IntPtr  ptr = FindWindow (null, "Program Manager") ;
            if (ptr != IntPtr.Zero)
		      ShowWindow (ptr, SW_HIDE);
        }
        public static void      ShowIcons()
        {
            IntPtr hProgMan = FindWindow (null, "Program Manager") ;
	        if (hProgMan != IntPtr.Zero)
		        ShowWindow (hProgMan, SW_SHOW);
        }
        /*public static void      ChangeIconsStyle()
        {
	        STYLESTRUCT ss;
	        HWND hDesk = GetWindow(GetWindow(FindWindow("Progman", NULL), GW_CHILD), GW_CHILD);
	        ss.styleOld = ss.styleNew = GetWindowLong(hDesk, GWL_STYLE);
	        if (ss.styleOld  2) ss.styleNew = ~2; else ss.styleNew |= 2;
	        SetWindowLong(hDesk, GWL_STYLE, ss.styleNew);
	        SendMessage(hDesk, WM_STYLECHANGED, (WPARAM)GWL_STYLE, (LPARAM)ss); 
        }*/
    }
}
