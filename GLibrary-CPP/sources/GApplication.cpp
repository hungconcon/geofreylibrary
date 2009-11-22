
#include "GApplication.h"

#if defined(GUNIX) & defined(X11)
Display *GApplication::_display = NULL;
#endif

void	GApplication::Initialize(int, char **)
{
	GApplication::Initialize();
}

void	GApplication::Initialize(void)
{
#if defined(GWIN)
	INITCOMMONCONTROLSEX test;
	test.dwSize = sizeof(test);
	test.dwICC = ICC_WIN95_CLASSES;
	if (!InitCommonControlsEx(&test))
		throw GException("GApplication", "Cannot init common controls !");
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR  gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
#elif defined(GUNIX) & defined(X11)
	_display = XOpenDisplay(NULL);
    if (_display == NULL)
		throw GException("GApplication", "Cannot connect to Xserver !");
#endif
}

void	GApplication::Execute(void)
{
#if defined(GWIN)
	MSG Msg;
	while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
#elif defined(GUNIX) & defined(X11)
	XCloseDisplay(_display);
#endif
}

#if defined(GUNIX) & defined(X11)

Display	*GApplication::GetDisplay(void)
{
	return (_display);
}

#endif