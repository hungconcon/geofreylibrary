
#include "GSocketSelector.h"

GSocketSelector::GSocketSelector(void)
{
	this->_tv.tv_sec = 0;
	this->_tv.tv_usec = 50;
	FD_ZERO(&(this->_fdRead));
	FD_ZERO(&(this->_fdWrite));
	this->_max = 0;
	this->_timeOut = true;
}

GSocketSelector::~GSocketSelector(void)
{

}

void	GSocketSelector::SetTimeOut(unsigned int MilliSecond)
{
	if (MilliSecond == 0)
		this->_timeOut = false;
	else
	{
		this->_tv.tv_usec = MilliSecond;
		this->_tv.tv_sec = 0;
	}
}

GSocketList	GSocketSelector::GetSocketRead(void) const
{
	return (this->_read);
}

GSocketList	GSocketSelector::GetSocketWrite(void) const
{
	return (this->_write);
}

void		GSocketSelector::AddRead(GISocket *Socket)
{
	if (!this->_rw.Contain(Socket))
	{
		this->_rw.PushBack(Socket);
		FD_SET(Socket->GetSocket(), &(this->_fdRead));
		if (this->_max < Socket->GetSocket())
			this->_max = Socket->GetSocket();
	}
}
void		GSocketSelector::AddRead(GVector<GISocket*> SocketVector)
{
	unsigned int i = 0;
	unsigned int size = this->_read.Size();
	while (i < size)
	{
		if (!this->_rw.Contain(SocketVector[i]))
		{
			this->_rw.PushBack(SocketVector[i]);
			FD_SET(SocketVector[i]->GetSocket(), &(this->_fdRead));
			if (this->_max < SocketVector[i]->GetSocket())
				this->_max = SocketVector[i]->GetSocket();
			++i;
		}
	}
}

void		GSocketSelector::AddWrite(GISocket *Socket)
{
	if (!this->_rw.Contain(Socket))
	{
		this->_rw.PushBack(Socket);
			FD_SET(Socket->GetSocket(), &(this->_fdWrite));
		if (this->_max < Socket->GetSocket())
			this->_max = Socket->GetSocket();
	}
}
void		GSocketSelector::AddWrite(GVector<GISocket*> SocketVector)
{
	unsigned int i = 0;
	unsigned int size = this->_read.Size();
	while (i < size)
	{
		if (!this->_rw.Contain(SocketVector[i]))
		{
			this->_rw.PushBack(SocketVector[i]);
			FD_SET(SocketVector[i]->GetSocket(), &(this->_fdWrite));
			if (this->_max < SocketVector[i]->GetSocket())
				this->_max = SocketVector[i]->GetSocket();
		}
		++i;
	}
}

void		GSocketSelector::Select(void)
{
	if (this->_timeOut)
	{
		if (select(this->_max + 1, &(this->_fdRead), &(this->_fdWrite), NULL, &this->_tv) < 0)
			throw GException("GSocketSelector", "Select error");
	}
	else
	{
		if (select(this->_max + 1, &(this->_fdRead), &(this->_fdWrite), NULL, NULL) < 0)
			throw GException("GSocketSelector", "Select error");
	}
	this->_read.Clear();
	this->_write.Clear();
	unsigned int i = 0;
	unsigned int size = this->_rw.Size();
	while (i < size)
	{
		if (FD_ISSET(this->_rw[i]->GetSocket(), &(this->_fdRead)))
			this->_read.PushBack(this->_rw[i]);
		if (FD_ISSET(this->_rw[i]->GetSocket(), &(this->_fdWrite)))
			this->_write.PushBack(this->_rw[i]);
		++i;
	}
	FD_ZERO(&(this->_fdRead));
	FD_ZERO(&(this->_fdWrite));
	this->_rw.Clear();	
	this->_max = 0;
}


