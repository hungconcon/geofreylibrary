
#include "GDateTime.h"

GDateTime::GDateTime(void)
{
	time_t tt;
	time (&tt);
#if defined (WIN32) | defined (_WIN32) |  defined (__WIN32) | defined (WIN64) | defined (_WIN64) | defined (__WIN64)
	this->_tm = new tm;
	localtime_s(this->_tm, &tt);
#else
	this->_tm = localtime(&tt);
#endif
}

GDateTime::GDateTime(const GDate &d)
{
	this->_tm = new tm;
	this->_tm->tm_mon = d.Month() - 1;
	this->_tm->tm_year = d.Year() - 1900;
	this->_tm->tm_wday = d.DayWeek();
	this->_tm->tm_yday = d.DayYear();
	this->_tm->tm_mday = d.Day() - 1;
}

GDateTime::GDateTime(const GTime &Time)
{
	this->_tm = new tm;
	this->_tm->tm_hour = Time.Hour();
	this->_tm->tm_min = Time.Min();
	this->_tm->tm_sec = Time.Sec();
}

GDateTime::GDateTime(const GDate &Date, const GTime &Time)
{
	this->_tm = new tm;
	this->_tm->tm_hour = Time.Hour();
	this->_tm->tm_mday = Date.Day() - 1;
	this->_tm->tm_min = Time.Min();
	this->_tm->tm_mon = Date.Month() - 1;
	this->_tm->tm_sec = Time.Sec();
	this->_tm->tm_year = Date.Year() - 1900;
	this->_tm->tm_wday = Date.DayWeek();
	this->_tm->tm_yday = Date.DayYear();
}

GDateTime::GDateTime(int y, int M, int d, int h, int m, int s)
{
	this->_tm = new tm;
	if (y < 0)
		GWarning::Warning("GDateTime", "GDateTime(int Y, int M, int D, int h, int m, int s)", "Year is out of range !");
	if (M < 1 || M > 12)
		GWarning::Warning("GDateTime", "GDateTime(int Y, int M, int D, int h, int m, int s)", "Month is out of range !");
	if (d < 1 || d > 31)
		GWarning::Warning("GDateTime", "GDateTime(int Y, int M, int D, int h, int m, int s)", "Day is out of range !");
	if (h < 0 || h > 23)
		GWarning::Warning("GDateTime", "GDateTime(int Y, int M, int D, int h, int m, int s)", "Hours is out of range !");
	if (m < 0 || m > 59)
		GWarning::Warning("GDateTime", "GDateTime(int Y, int M, int D, int h, int m, int s)", "Minutes is out of range !");
	if (s < 0 || s > 59)
		GWarning::Warning("GDateTime", "GDateTime(int Y, int M, int D, int h, int m, int s)", "Secondes is out of range !");
	this->_tm->tm_year = y - 1900;
	this->_tm->tm_mon = M;
	this->_tm->tm_mday = d;
	this->_tm->tm_hour = h;
	this->_tm->tm_min = m;
	this->_tm->tm_sec = s;
	mktime(this->_tm);
}

GDateTime::~GDateTime(void)
{
	delete this->_tm;
}

int			GDateTime::Hour(void) const
{
	return (this->_tm->tm_hour);
}

int			GDateTime::Min(void) const
{
	return (this->_tm->tm_min);
}

int			GDateTime::Sec(void) const
{
	return (this->_tm->tm_sec);
}
void		GDateTime::AddHours(int h)
{
	this->_tm->tm_hour += h;
	mktime(this->_tm);
}
void		GDateTime::AddMins(int m)
{
	this->_tm->tm_min += m;
	mktime(this->_tm);
}
void		GDateTime::AddSecs(int s)
{
	this->_tm->tm_sec += s;
	mktime(this->_tm);
}

int			GDateTime::Day(void) const
{
	return (this->_tm->tm_mday + 1);
}

int			GDateTime::Month(void) const
{
	return (this->_tm->tm_mon + 1);
}

int			GDateTime::Year(void) const
{
	return (this->_tm->tm_year + 1900);
}
int			GDateTime::DayYear(void) const
{
	return (this->_tm->tm_yday);
}
int			GDateTime::DayWeek(void) const
{
	return (this->_tm->tm_wday);
}
bool		GDateTime::IsBisextile(void) const
{
	return (this->_tm->tm_year % 4 == 0 && this->_tm->tm_year != 100 || this->_tm->tm_year % 400 == 0);
}

int			GDateTime::GetNumberDayMonth(void) const
{
	switch (this->_tm->tm_mon) 
	{
		case 1 : case 3 : case 5: case 7 : case 8 : case 10 : case 12 :
			return (31);
		case 4 : case 6 : case 9 : case 11 :
			return (30);
		case 2 :
			return (this->IsBisextile()) ? 29 : 28;
	}
	return (0);
}
void		GDateTime::AddYears(int y)
{
	this->_tm->tm_year += y;
	mktime(this->_tm);
}
void		GDateTime::AddMonths(int m)
{
	this->_tm->tm_mon += m;
	mktime(this->_tm);
}
void		GDateTime::AddDays(int d)
{
	this->_tm->tm_mday += d;
	mktime(this->_tm);
}

void		GDateTime::SetDate(int y, int m, int d)
{
	if (y < 0)
		GWarning::Warning("GDate", "GDate(int Y, int M, int D)", "Year is out of range !");
	if (m < 1 || m > 12)
		GWarning::Warning("GDate", "GDate(int Y, int M, int D)", "Month is out of range !");
	if (d < 1 || d > 31)
		GWarning::Warning("GDate", "GDate(int Y, int M, int D)", "Day is out of range !");
	this->_tm->tm_mon = m;
	this->_tm->tm_mday = d;
	this->_tm->tm_year = y;
	mktime(this->_tm);
}

void		GDateTime::SetTime(int h, int m, int s)
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

int			GDateTime::GetNumberDayMonth(int m, int y)
{
	switch (m) 
	{
		case 1 : case 3 : case 5: case 7 : case 8 : case 10 : case 12 :
			return (31);
		case 4 : case 6 : case 9 : case 11 :
			return (30);
		case 2 :
			return (GDate::IsBisextile(y)) ? 29 : 28;
	}
	return 0;
}
bool		GDateTime::IsBisextile(int y)
{
	return (y % 4 == 0 && y != 100 || y % 400 == 0);
}
GString		GDateTime::GetDateTime(const GString &format, G::LanguageOption op)
{
	GString g(format);
	GString test(this->_tm->tm_mday);
	DayInterface *d = GDayInstance::GetInstance(op);
	g = g.Replace("%dddd", d->GetDay(this->_tm->tm_wday));
	g = g.Replace("%ddd", d->GetTruncateDay(this->_tm->tm_wday));
	g = g.Replace("%dd", test.RightJustified(2, '0'));
	g = g.Replace("%d", test);
	MonthInterface *m = GMonthInstance::GetInstance(op);
	test = (this->_tm->tm_mon + 1);
	g = g.Replace("%MMMM", m->GetMonth(this->_tm->tm_mon));
	g = g.Replace("%MMM", m->GetTruncateMonth(this->_tm->tm_mon));
	g = g.Replace("%MM", test.RightJustified(2, '0'));
	g = g.Replace("%M", this->_tm->tm_mon + 1);
	test = this->_tm->tm_year + 1900;
	g = g.Replace("%yyyy", test);
	g = g.Replace("%yy", test.Substr(2, 4));
	test = this->_tm->tm_hour;
	g = g.Replace("%hh", test.RightJustified(2, '0'));
	g = g.Replace("%h", test);
	test = this->_tm->tm_min;
	g = g.Replace("%mm", test.RightJustified(2, '0'));
	g = g.Replace("%m", test);
	test = this->_tm->tm_sec;
	g = g.Replace("%ss", test.RightJustified(2, '0'));
	g = g.Replace("%s", test);
	delete d;
	delete m;
	return (g);
}
bool		GDateTime::operator!=(const GDateTime &d) const
{
	if (this->_tm->tm_mday != d._tm->tm_mday)
		return (true);
	if (this->_tm->tm_mon != d._tm->tm_mon)
		return (true);
	if (this->_tm->tm_year != d._tm->tm_year)
		return (true);
	if (this->_tm->tm_hour != d._tm->tm_hour)
		return (true);
	if (this->_tm->tm_min != d._tm->tm_min)
		return (true);
	if (this->_tm->tm_sec != d._tm->tm_sec)
		return (true);
	return (false);
}
bool		GDateTime::operator<(const GDateTime &d) const
{
	if (this->_tm->tm_year < d._tm->tm_year)
		return (true);
	if (this->_tm->tm_year > d._tm->tm_year)
		return (false);
	if (this->_tm->tm_mon < d._tm->tm_mon)
		return (true);
	if (this->_tm->tm_mon > d._tm->tm_mon)
		return (false);
	if (this->_tm->tm_mday < d._tm->tm_mday)
		return (true);
	if (this->_tm->tm_mday > d._tm->tm_mday)
		return (false);
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
bool		GDateTime::operator<=(const GDateTime &d) const
{
	if (this->_tm->tm_year < d._tm->tm_year)
		return (true);
	if (this->_tm->tm_year > d._tm->tm_year)
		return (false);
	if (this->_tm->tm_mon < d._tm->tm_mon)
		return (true);
	if (this->_tm->tm_mon > d._tm->tm_mon)
		return (false);
	if (this->_tm->tm_mday < d._tm->tm_mday)
		return (true);
	if (this->_tm->tm_mday > d._tm->tm_mday)
		return (false);
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
bool		GDateTime::operator==(const GDateTime &d) const
{
	if (this->_tm->tm_mday != d._tm->tm_mday)
		return (false);
	if (this->_tm->tm_mon != d._tm->tm_mon)
		return (false);
	if (this->_tm->tm_year != d._tm->tm_year)
		return (false);
	if (this->_tm->tm_mday != d._tm->tm_mday)
		return (false);
	if (this->_tm->tm_mon != d._tm->tm_mon)
		return (false);
	if (this->_tm->tm_year != d._tm->tm_year)
		return (false);
	return (true);
}
bool		GDateTime::operator>(const GDateTime &d) const
{
	if (this->_tm->tm_year < d._tm->tm_year)
		return (false);
	if (this->_tm->tm_year > d._tm->tm_year)
		return (true);
	if (this->_tm->tm_mon < d._tm->tm_mon)
		return (false);
	if (this->_tm->tm_mon > d._tm->tm_mon)
		return (true);
	if (this->_tm->tm_mday < d._tm->tm_mday)
		return (false);
	if (this->_tm->tm_mday > d._tm->tm_mday)
		return (true);
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
bool		GDateTime::operator>=(const GDateTime &d) const
{
	if (this->_tm->tm_year < d._tm->tm_year)
		return (false);
	if (this->_tm->tm_year > d._tm->tm_year)
		return (true);
	if (this->_tm->tm_mon < d._tm->tm_mon)
		return (false);
	if (this->_tm->tm_mon > d._tm->tm_mon)
		return (true);
	if (this->_tm->tm_mday < d._tm->tm_mday)
		return (false);
	if (this->_tm->tm_mday > d._tm->tm_mday)
		return (true);
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
unsigned int	GDateTime::GetTimeStamp(void) const
{
	return ((unsigned int)mktime(this->_tm));
}
