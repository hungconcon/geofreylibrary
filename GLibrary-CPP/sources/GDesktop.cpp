
#include "GDesktop.h"

void	GDesktop::HideIcons(void)
{
#if defined (GWIN)
	HWND hProgMan = ::FindWindow (NULL, "Program Manager") ;
	if (hProgMan)
		::ShowWindow (hProgMan, SW_HIDE);
#else

#endif

}
void	GDesktop::ShowIcons(void)
{
#if defined (GWIN)
	HWND hProgMan = ::FindWindow (NULL, "Program Manager") ;
	if (hProgMan)
		::ShowWindow (hProgMan, SW_SHOW);
#else

#endif
}

void	GDesktop::ChangeIconsStyle(void)
{
#if defined (GWIN)
	STYLESTRUCT ss;
	HWND hDesk = GetWindow(GetWindow(FindWindow("Progman", NULL), GW_CHILD), GW_CHILD);
	ss.styleOld = ss.styleNew = GetWindowLong(hDesk, GWL_STYLE);
	if(ss.styleOld & 2) ss.styleNew &= ~2; else ss.styleNew |= 2;
	SetWindowLong(hDesk, GWL_STYLE, ss.styleNew);
	SendMessage(hDesk, WM_STYLECHANGED, (WPARAM)GWL_STYLE, (LPARAM)&ss); 
#else

#endif
}
