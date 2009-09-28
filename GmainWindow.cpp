
#include "GMainWindow.h"

LRESULT CALLBACK MainProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT paintst;
	switch (mes)
	{
	case WM_PAINT:
		hDC=BeginPaint(hWnd,&paintst);
		EndPaint(hWnd,&paintst);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, mes, wParam, lParam);
	}
}

GMainWindow::GMainWindow(void)
{
#if defined (GWIN)
	this->_x = 200;
	this->_y = 100;
    this->_classe.cbSize = sizeof(WNDCLASSEX);
    this->_classe.style = CS_HREDRAW|CS_VREDRAW;
	this->_classe.lpfnWndProc = MainProc;
    this->_classe.cbClsExtra = 0;
    this->_classe.cbWndExtra = 0;
	
    this->_classe.hInstance=  this->_hInstance;
    this->_classe.hIcon=LoadIcon(NULL,IDI_APPLICATION);
    this->_classe.hCursor=LoadCursor(NULL,IDC_ARROW);
    this->_classe.hbrBackground=reinterpret_cast<HBRUSH>(COLOR_WINDOW+1);
    this->_classe.lpszMenuName=NULL;
    this->_classe.lpszClassName="std";
    this->_classe.hIconSm=LoadIcon(NULL,IDI_APPLICATION);
	RegisterClassEx(& this->_classe);
	this->_widget = CreateWindowEx(	WS_EX_CLIENTEDGE, "std", "GMainWindow", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,  this->_hInstance, NULL);
#endif
}

/*void	GMainWindow::CreateGui(void)
{
 	 this->_mutex.Unlock();
	 ShowWindow(this->_widget, SW_SHOW);
	MSG msg;
	while(true)
	{
		if (GetMessage(&msg,NULL,0,0)==TRUE)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//else
		//	break;
	}
}
*/

GMainWindow::~GMainWindow(void)
{

}

void	GMainWindow::SetTitle(const GString &Title)
{
#if defined (GWIN)
	char	*ttl = Title.ToChar();
	if (SendMessage(this->_widget, WM_SETTEXT, NULL, (LPARAM)ttl) == 0)
	{
		delete[] ttl;
		throw GException("GMainWindow", "Canot change title !");
	}
	delete[] ttl;
#endif
}
