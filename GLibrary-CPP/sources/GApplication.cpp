
#include "GApplication.h"

#if defined(GUNIX)
Display *GApplication::_display = NULL;
#endif

void	GApplication::Initialize(int argc, char **argv)
{
#if defined(GWIN)
	INITCOMMONCONTROLSEX test;
	test.dwSize = sizeof(test);
	test.dwICC = ICC_WIN95_CLASSES;
	if (!InitCommonControlsEx(&test))
		throw GException("GApplication", "Cannot init common controls !");
#elif defined(GUNIX)
	_display = XOpenDisplay(NULL);
    if (_display == NULL)
		throw GException("GApplication", "Cannot connect to Xserver !");
#endif
}

void	GApplication::Initialize(void)
{
#if defined(GWIN)
	INITCOMMONCONTROLSEX test;
	test.dwSize = sizeof(test);
	test.dwICC = ICC_WIN95_CLASSES;
	if (!InitCommonControlsEx(&test))
		throw GException("GApplication", "Cannot init common controls !");
#elif defined(GUNIX)
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
#elif defined(GUNIX)
	XCloseDisplay(_display);
#endif
}

#if defined(GUNIX)

Display	*GApplication::GetDisplay(void)
{
	return (_display);
}

#endif