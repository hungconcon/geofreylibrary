
#include "Gmouse.h"

void	GMouse::HideCursor(void)
{
	HCURSOR hcurseur = LoadCursor(GetModuleHandle(NULL),"IDC_CURSOR");
	HCURSOR hcopiecurseur = CopyCursor(hcurseur);
	SetSystemCursor(hcopiecurseur, OCR_APPSTARTING);
	hcopiecurseur = CopyCursor(hcurseur);
	SetSystemCursor(hcopiecurseur, OCR_NORMAL);
}

void	GMouse::ShowCursor(void)
{
	SystemParametersInfo(SPI_SETCURSORS, 0, 0, 0); 
}