
#include "GTime.h"

GTime::GTime(void)
{
	time_t tt;
	time (&tt);
#if defined (GWIN)
	this->_tm = new tm;
	localtime_s(this->_tm, &tt);
#else
	this->_tm = localtime(&tt);
#endif
	
}

GTime::GTime(const GTime &d)
{
	this->_tm = new tm;
	this->_tm->tm_hour = d._tm->tm_hour;
	this->_tm->tm_isdst = d._tm->tm_isdst;
	this->_tm->tm_mday = d._tm->tm_mday;
	this->_tm->tm_min = d._tm->tm_min;
	this->_tm->tm_mon = d._tm->tm_mon;
	this->_tm->tm_sec = d._tm->tm_sec;
	this->_tm->tm_year = d._tm->tm_year;
	this->_tm->tm_wday = d._tm->tm_wday;
	this->_tm->tm_yday = d._tm->tm_yday;
}

GTime::GTime(int h, int m, int s)
{
	if (h < 0 || h > 23)
		GWarning::Warning("GTime", "GTime(int Hours, int Minutes, int Seconds)", "Hours is out of range !");
	if (m < 0 || m > 59)
		GWarning::Warning("GTime", "GTime(int Hours, int Minutes, int Seconds)", "Minutes is out of range !");
	if (s < 0 || s > 59)
		GWarning::Warning("GTime", "GTime(int Hours, int Minutes, int Seconds)", "Secondes is out of range !");
	time_t tt;
	time (&tt);
#if defined (GWIN)
	this->_tm = new tm;
	localtime_s(this->_tm, &tt);
#else
	this->_tm = localtime(&tt);
#endif
	this->_tm->tm_hour = h;
	this->_tm->tm_min = m;
	this->_tm->tm_sec = s;
	mktime(this->_tm);
}

GTime::~GTime(void)
{

}

int			GTime::Hour(void) const
{
	return (this->_tm->tm_hour);
}

int			GTime::Min(void) const
{
	return (this->_tm->tm_min);
}

int			GTime::Sec(void) const
{
	return (this->_tm->tm_sec);
}
void		GTime::AddHours(int h)
{
	this->_tm->tm_hour += h;
	mktime(this->_tm);
}
void		GTime::AddMins(int m)
{
	this->_tm->tm_min += m;
	mktime(this->_tm);
}
void		GTime::AddSecs(int s)
{
	this->_tm->tm_sec += s;
	mktime(this->_tm);
}
void		GTime::SetTime(int h, int m, int s)
{
	if (h < 0 || h > 23)
		GWarning::Warning("GTime", "GTime(int Hours, int Minutes, int Seconds)", "Hours is out of range !");
	if (m < 0 || m > 59)
		GWarning::Warning("GTime", "GTime(int Hours, int Minutes, int Seconds)", "Minutes is out of range !");
	if (s < 0 || s > 59)
		GWarning::Warning("GTime", "GTime(int Hours, int Minutes, int Seconds)", "Secondes is out of range !");
	this->_tm->tm_hour = h;
	this->_tm->tm_min = m;
	this->_tm->tm_sec = s;
	mktime(this->_tm);
}

GString		&GTime::GetTime(const GString &format)
{
	GString *g = new GString(format);
	GString test(this->_tm->tm_hour);
	*g = g->Replace("%hh", test.RightJustified(2, '0'));
	*g = g->Replace("%h", test);
	test = this->_tm->tm_min;
	*g = g->Replace("%mm", test.RightJustified(2, '0'));
	*g = g->Replace("%m", test);
	test = this->_tm->tm_sec;
	*g = g->Replace("%ss", test.RightJustified(2, '0'));
	*g = g->Replace("%s", test);
	return (*g);
}
bool		GTime::operator!=(const GTime &d) const
{
	if (this->_tm->tm_hour != d._tm->tm_hour)
		return (true);
	if (this->_tm->tm_min != d._tm->tm_min)
		return (true);
	if (this->_tm->tm_sec != d._tm->tm_sec)
		return (true);
	return (false);
}
bool		GTime::operator<(const GTime &d) const
{
	if (this->_tm->tm_hour < d._tm->tm_hour)
		return (true);
	if (this->_tm->tm_hour > d._tm->tm_hour)
		return (false);
	if (this->_tm->tm_min < d._tm->tm_min)
		return (true);
	if (this->_tm->tm_min > d._tm->tm_min)
		return (false);
	if (this->_tm->tm_sec < d._tm->tm_sec)
		return (true);
	if (this->_tm->tm_sec > d._tm->tm_sec)
		return (false);
	return (false);
}
bool		GTime::operator<=(const GTime &d) const
{
	if (this->_tm->tm_hour < d._tm->tm_hour)
		return (true);
	if (this->_tm->tm_hour > d._tm->tm_hour)
		return (false);
	if (this->_tm->tm_min < d._tm->tm_min)
		return (true);
	if (this->_tm->tm_min > d._tm->tm_min)
		return (false);
	if (this->_tm->tm_sec < d._tm->tm_sec)
		return (true);
	if (this->_tm->tm_sec > d._tm->tm_sec)
		return (false);
	return (true);
}
bool		GTime::operator==(const GTime &d) const
{
	if (this->_tm->tm_mday != d._tm->tm_mday)
		return (false);
	if (this->_tm->tm_mon != d._tm->tm_mon)
		return (false);
	if (this->_tm->tm_year != d._tm->tm_year)
		return (false);
	return (true);
}
bool		GTime::operator>(const GTime &d) const
{
	if (this->_tm->tm_hour < d._tm->tm_hour)
		return (false);
	if (this->_tm->tm_hour > d._tm->tm_hour)
		return (true);
	if (this->_tm->tm_min < d._tm->tm_min)
		return (false);
	if (this->_tm->tm_min > d._tm->tm_min)
		return (true);
	if (this->_tm->tm_sec < d._tm->tm_sec)
		return (false);
	if (this->_tm->tm_sec > d._tm->tm_sec)
		return (true);
	return (false);
}
bool		GTime::operator>=(const GTime &d) const
{
	if (this->_tm->tm_hour < d._tm->tm_hour)
		return (false);
	if (this->_tm->tm_hour > d._tm->tm_hour)
		return (true);
	if (this->_tm->tm_min < d._tm->tm_min)
		return (false);
	if (this->_tm->tm_min > d._tm->tm_min)
		return (true);
	if (this->_tm->tm_sec < d._tm->tm_sec)
		return (false);
	if (this->_tm->tm_sec > d._tm->tm_sec)
		return (true);
	return (true);
}

