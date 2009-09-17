#if defined (WIN32) | defined (_WIN32) |  defined (__WIN32) | defined (WIN64) | defined (__WIN64)
	#define GEXPORTED __declspec(dllexport)
	#define GWIN
#else
	#define GUNIX	
	#define GEXPORTED
#endif
