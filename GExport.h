#if defined (WIN32) | defined (_WIN32) |  defined (__WIN32) | defined (WIN64) | defined (__WIN64)
	#define GEXPORTED __declspec(dllexport)
	#define GWIN
#elif defined(linux) || defined(__linux) || defined(__linux__)
	#define GLINUX
	#define GUNIX
	#define GEXPORTED
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
	#define GBSD
	#define GUNIX
	#define GEXPORTED
#elif defined (sun) || defined (__sun) || defined (__sun__) ||  defined (_OS_SUN_) || defined (__SVR4)
	#define GSUN
	#define GUNIX
	#define GEXPORTED
#endif
