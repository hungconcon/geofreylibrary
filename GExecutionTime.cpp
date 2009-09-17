#include "GExecutionTime.h"

GExecutionTime::GExecutionTime(void) : _started(false)
{
}

GExecutionTime::~GExecutionTime(void)
{
}

void			GExecutionTime::Start(void)
{
	if (!this->_started)
	{
		this->_begin.Now();
		this->_started = true;
	}
}

GPrecisionTime	GExecutionTime::Now(void)
{
	if (this->_started)
	{
		GPrecisionTime	now;
		return (this->_begin - now);
	}
	return (GPrecisionTime::Null());
}

GPrecisionTime	GExecutionTime::Stop(void)
{
	if (this->_started)
	{
		GPrecisionTime	now;
		return (this->_begin - now);
		this->_started = false;
	}
	return (GPrecisionTime::Null());
}

GPrecisionTime	GExecutionTime::Restart(void)
{
	GPrecisionTime	t(this->Stop());
	this->Start();
	return (t);
}
