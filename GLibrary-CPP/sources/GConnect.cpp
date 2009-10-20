
#include "GConnect.h"

GThread		*GConnect::_Thread = NULL;
GPointerMap	GConnect::_Map = GPointerMap();
GMutex		GConnect::_Mutex = GMutex();

void	GConnect::Connect(const GString &Name, GFunction f)
{
	if (_Thread == NULL)
	{
		_Thread = new GThread(&GConnect::Check);
		_Thread->Start();
	}
	AddConnect(Name, f);
}

void	GConnect::Disconnect(const GString &Name)
{
	if (_Thread)
		RemoveConnect(Name);
}

void	GConnect::AddConnect(const GString &Name, GFunction f)
{
	_Mutex.Lock();
	_Map[Name] = GPair(f, false);
	_Mutex.Unlock();
}

void	GConnect::RemoveConnect(const GString &Name)
{
	_Mutex.Lock();
	_Mutex.Unlock();
}

void	GConnect::StopThread(void)
{
	if (_Thread)
		_Thread->Abort();
}

void	GConnect::StartThread(void)
{
	if (_Thread == NULL)
		_Thread = new GThread(&GConnect::Check);
	_Thread->Start();
}

void	*GConnect::Check(void *)
{
	while (true)
	{
		
	}
}