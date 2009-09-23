
#include "GMutex.h"

GMutex::GMutex(void)
{
#if defined (GWIN)
	InitializeCriticalSection(&this->_cr_sct);
	this->_mutex = CreateMutex(NULL, false, NULL);
#elif defined(GBSD)
	this->_mutex = PTHREAD_MUTEX_INITIALIZER;
#elif defined(GLINUX)
	pthread_mutex_init(&this->_mutex, NULL);
#endif
}

GMutex::~GMutex(void)
{
#if defined (GWIN)
	DeleteCriticalSection(&this->_cr_sct);
#endif
}

void	GMutex::Lock(void)
{
#if defined (GWIN)
	EnterCriticalSection(&this->_cr_sct);
	WaitForSingleObject(this->_mutex, INFINITE);
#else
	pthread_mutex_lock(&this->_mutex);
#endif
}

void	GMutex::TryLock(void)
{
#if defined (GWIN)
	WaitForSingleObject(this->_mutex, 1);
#else
	pthread_mutex_trylock(&this->_mutex);
#endif
}

void	GMutex::Unlock(void)
{
#if defined (GWIN)
	LeaveCriticalSection(&this->_cr_sct);
	ReleaseMutex(this->_mutex);
#else
	pthread_mutex_unlock(&this->_mutex);
#endif
}

bool	GMutex::IsLock(void) const
{
	return (this->_lock);
}
