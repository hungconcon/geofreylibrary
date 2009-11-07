
#include "GMainWindow.h"

void	Resize(GWidgetHandle Handle)
{
	GWidget *widget = GWidget::GetWidgetByHandle(Handle);
	if (widget == NULL)
		return ;
	widget->SetSize();
	GSize s = widget->GetCurrentSize();
	GSize s_max = widget->GetMaximumSize();
	GSize s_min = widget->GetMinimumSize();
	GSize news = s;
	if (s_max.GetX() != 0 && s.GetX() > s_max.GetX())
		news.SetX(s_max.GetX());
	if (s_max.GetY() != 0 && s.GetY() > s_max.GetY())
		news.SetY(s_max.GetY());
	if (s_min.GetX() != 0 && s.GetX() < s_min.GetX())
		news.SetX(s_min.GetX());
	if (s_min.GetY() != 0 && s.GetY() < s_min.GetY())
		news.SetY(s_min.GetY());
	widget->SetSize(news);
}

#if defined(GWIN)
LRESULT CALLBACK MainProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT paintst;
	switch (mes)
	{
	case WM_PAINT:
		hDC=BeginPaint(hWnd,&paintst);
		EndPaint(hWnd,&paintst);
		return (0);
	case WM_DESTROY:
		PostQuitMessage(0);
		return (0);
	case WM_SIZE:
		Resize(hWnd);
		return (0);
	default:
		return DefWindowProc(hWnd, mes, wParam, lParam);
	}
}
#endif

GMainWindow::GMainWindow(void)
{
#if defined (GWIN)
	this->_x = 200;
	this->_y = 100;
    this->_classe.cbSize = sizeof(WNDCLASSEX);
    this->_classe.style = 0;
	this->_classe.lpfnWndProc = MainProc;
    this->_classe.cbClsExtra = 0;
    this->_classe.cbWndExtra = 0;
    this->_classe.hInstance=  NULL;
    this->_classe.hIcon=LoadIcon(NULL, IDI_APPLICATION);
    this->_classe.hCursor=LoadCursor(NULL, IDC_ARROW);
    this->_classe.hbrBackground= (HBRUSH)(1 + COLOR_BTNFACE);

    this->_classe.lpszMenuName=NULL;
    this->_classe.lpszClassName="std";
    this->_classe.hIconSm=LoadIcon(NULL,IDI_APPLICATION);
	RegisterClassEx(&this->_classe);
	//this->_widget = CreateWindowEx(	WS_EX_CLIENTEDGE, "std", "GMainWindow", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,  this->_hInstance, NULL);
	this->_widget = CreateWindow("std", "GMainWindow", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,  NULL, NULL);
#endif
}

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

void	GMainWindow::Destroy(void)
{
#if defined (GWIN)
	if (SendMessage(this->_widget, WM_DESTROY , NULL, NULL) == 0)
	{
		
	}
#endif

}