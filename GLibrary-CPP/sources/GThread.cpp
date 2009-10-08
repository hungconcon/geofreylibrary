
#include "GThread.h"

GThread::GThread(GFunction ptr)
{
	this->_set = true;
	this->_start = false;
	this->_function = ptr;
}

GThread::GThread(void)
{
	this->_set = false;
	this->_start = false;
}

GThread::~GThread(void)
{

}

void	GThread::Abort(void)
{
	if (this->_set == true && this->_start == true)
	{
#if defined (GWIN)
		ExitThread(NULL);
#else
		pthread_exit(NULL);
#endif
	}
}

void	GThread::Start(void *arg)
{
	if (this->_set == true && !this->_start)
	{
#if defined (GWIN)
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)this->_function, arg, NULL, &this->_id);
#else
		pthread_create(&this->_thread, NULL, this->_function, arg);
#endif
	}
}

void	GThread::Start(void)
{
  this->Start(NULL);
}

void	GThread::SetFunction(GFunction f)
{
	if (!this->_set)
	{
		this->_set = true;
		this->_function = f;
	}
}

GThreadId	GThread::GetId(void) const
{
	return (this->_id);
}


