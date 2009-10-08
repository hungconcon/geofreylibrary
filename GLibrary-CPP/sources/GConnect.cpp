
#include "GConnect.h"

GThread		*GConnect::Thread = NULL;
GPointerMap	*GConnect::Map = new GPointerMap();
GMutex		*GConnect::Mutex = new GMutex();

void	GConnect::Connect(const GString &, GFunction f)
{
	if (Thread == NULL)
	{
		Thread = new GThread(&GConnect::Check);
		Thread->Start();
	}
}

void	GConnect::StopThread(void)
{
	Thread->Abort();
}

void	GConnect::StartThread(void)
{
	Thread->Start();
}

void	*GConnect::Check(void *)
{
	//GThread *th;
	while (true)
	{
		
	}
}