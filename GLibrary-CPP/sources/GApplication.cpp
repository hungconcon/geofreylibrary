
#include "GApplication.h"

void	GApplication::Initialize(int argc, char **argv)
{
#if defined(GWIN)
	INITCOMMONCONTROLSEX test;
	test.dwSize = sizeof(test);
	test.dwICC = ICC_WIN95_CLASSES;
	if (!InitCommonControlsEx(&test))
		throw GException("GApplication", "Cannot init common controls !");
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
#endif
}