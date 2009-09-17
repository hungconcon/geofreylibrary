#include "GPrecisionTime.h"

GPrecisionTime::GPrecisionTime(void)
{
#ifdef _TIME64_T
	this->_now = GTimeOfDay64();
#else
	this->_now = GTimeOfDay();
#endif
}

GPrecisionTime::GPrecisionTime(const GPrecisionTime &p)
{
	this->_now = p._now;
}

GPrecisionTime::GPrecisionTime(struct timeval tv)
{
	this->_now.tv_sec = tv.tv_sec;
	this->_now.tv_usec = tv.tv_usec;
}

#ifdef _TIME64_T
GPrecisionTime::GPrecisionTime(struct timeval64 tv)
{
	this->_now = tv;
}
#endif

GPrecisionTime::~GPrecisionTime(void)
{
}

bool	GPrecisionTime::operator<(const GPrecisionTime &p) const
{
	if (this->_now.tv_sec < p._now.tv_sec)
		return (true);
	if (this->_now.tv_sec == p._now.tv_sec && this->_now.tv_usec < p._now.tv_usec)
		return (true);
	return (false);
}

bool	GPrecisionTime::operator==(const GPrecisionTime &p) const
{
	if (this->_now.tv_sec == p._now.tv_sec && this->_now.tv_usec == p._now.tv_usec)
		return (true);
	return (false);
}

GPrecisionTime	&GPrecisionTime::operator=(const GPrecisionTime &p)
{
	this->_now = p._now;
	return (*this);
}

GPrecisionTime	GPrecisionTime::operator-(const GPrecisionTime &p) const
{
	GPrecisionTime	n;
	if (p < *this)
		return (GPrecisionTime::Null());
	n._now.tv_sec = p._now.tv_sec - this->_now.tv_sec;
	n._now.tv_usec = p._now.tv_usec - this->_now.tv_usec;
	while (n._now.tv_usec < 0)
	{
		n._now.tv_usec = 1000000 + n._now.tv_usec;
		n._now.tv_sec--;
		if (n._now.tv_sec < 0)
			return (GPrecisionTime::Null());
	}
	return (n);
}

GPrecisionTime	GPrecisionTime::operator+(const GPrecisionTime &p) const
{
	GPrecisionTime	n;
	n._now.tv_sec = this->_now.tv_sec + p._now.tv_sec;
	n._now.tv_usec = this->_now.tv_usec + p._now.tv_usec;
	if (n._now.tv_usec > 1000000)
	{
		n._now.tv_usec -= 1000000;
		n._now.tv_sec++;
	}
	return (n);
}

GPrecisionTime	GPrecisionTime::Now(void)
{
#ifdef _TIME64_T
	this->_now = GTimeOfDay64();
#else
	this->_now = GTimeOfDay();
#endif
	return (*this);
}

GPrecisionTime	GPrecisionTime::SetTime(const GPrecisionTime &p)
{
	this->_now = p._now;
	return (p);
}

struct timeval	GPrecisionTime::GetTimeval(void)
{
	struct timeval	tv;
	tv.tv_sec = (long)this->_now.tv_sec;
	tv.tv_usec = this->_now.tv_usec;
	return (tv);
}

#ifdef _TIME64_T
struct timeval	GPrecisionTime::GetTimeval64(void)
{
	return (this->_now);
}
#endif

GPrecisionTime	GPrecisionTime::Null(void)
{
#ifdef _TIME64_T
	struct timeval64	tv;
#else
	struct timeval		tv;
#endif
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	return (GPrecisionTime(tv));
}

std::ostream &operator<<(std::ostream &os, const GPrecisionTime &p)
{
	os << p._now.tv_sec << ":" << p._now.tv_usec;
	return (os);
}
