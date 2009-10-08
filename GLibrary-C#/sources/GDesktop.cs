using System;

namespace G
{
    public class GDesktop
    {

        public static void      HideIcons()
        {
	        HWND hProgMan = FindWindow (NULL, "Program Manager") ;
        	if (hProgMan)
		        ShowWindow (hProgMan, SW_HIDE);
        }
        public static void      ShowIcons()
        {
            HWND hProgMan = FindWindow (NULL, "Program Manager") ;
	        if (hProgMan)
		        ShowWindow (hProgMan, SW_SHOW);
        }
        public static void      ChangeIconsStyle()
        {
	        STYLESTRUCT ss;
	        HWND hDesk = GetWindow(GetWindow(FindWindow("Progman", NULL), GW_CHILD), GW_CHILD);
	        ss.styleOld = ss.styleNew = GetWindowLong(hDesk, GWL_STYLE);
	        if (ss.styleOld & 2) ss.styleNew &= ~2; else ss.styleNew |= 2;
	        SetWindowLong(hDesk, GWL_STYLE, ss.styleNew);
	        SendMessage(hDesk, WM_STYLECHANGED, (WPARAM)GWL_STYLE, (LPARAM)&ss); 
        }
    }
}
