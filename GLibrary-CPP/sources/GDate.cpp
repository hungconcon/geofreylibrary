
#include "GDate.h"

GDate::GDate(void)
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

GDate::GDate(const GDate &d)
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

GDate::GDate(int y, int m, int d)
{
	if (y < 0)
		GWarning::Warning("GDate", "GDate(int Y, int M, int D)", "Year is out of range !");
	if (m < 1 || m > 12)
		GWarning::Warning("GDate", "GDate(int Y, int M, int D)", "Month is out of range !");
	if (d < 1 || d > 31)
		GWarning::Warning("GDate", "GDate(int Y, int M, int D)", "Day is out of range !");
	time_t tt;
	time (&tt);
#if defined (GWIN)
	this->_tm = new tm;
	localtime_s(this->_tm, &tt);
#else
	this->_tm = localtime(&tt);
#endif
	this->_tm->tm_mon = m - 1;
	this->_tm->tm_mday = d;
	this->_tm->tm_year = y - 1900;
	mktime(this->_tm);
}

GDate::~GDate(void)
{
}

int			GDate::Day(void) const
{
	return (this->_tm->tm_mday + 1);
}

int			GDate::Month(void) const
{
	return (this->_tm->tm_mon + 1);
}

int			GDate::Year(void) const
{
	return (this->_tm->tm_year + 1900);
}
int			GDate::DayYear(void) const
{
	return (this->_tm->tm_yday);
}
int			GDate::DayWeek(void) const
{
	return (this->_tm->tm_wday);
}
bool		GDate::IsBisextile(void) const
{
	return ((this->_tm->tm_year % 4 == 0 && this->_tm->tm_year != 100) || this->_tm->tm_year % 400 == 0);
}

int			GDate::GetNumberDayMonth(void) const
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
void		GDate::AddYears(int y)
{
	this->_tm->tm_year += y;
	mktime(this->_tm);
}
void		GDate::AddMonths(int m)
{
	this->_tm->tm_mon += m;
	mktime(this->_tm);
}
void		GDate::AddDays(int d)
{
	this->_tm->tm_mday += d;
	mktime(this->_tm);
}
void		GDate::SetDate(int y, int m, int d)
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

int			GDate::GetNumberDayMonth(int m, int y)
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
bool		GDate::IsBisextile(int y)
{
	return ((y % 4 == 0 && y != 100) || y % 400 == 0);
}
GString		GDate::GetDate(const GString &format, G::LanguageOption op)
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
	return (g);
}
bool		GDate::operator!=(const GDate &d) const
{
	if (this->_tm->tm_mday != d._tm->tm_mday)
		return (true);
	if (this->_tm->tm_mon != d._tm->tm_mon)
		return (true);
	if (this->_tm->tm_year != d._tm->tm_year)
		return (true);
	return (false);
}
bool		GDate::operator<(const GDate &d) const
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
	return (false);
}
bool		GDate::operator<=(const GDate &d) const
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
	return (true);
}
bool		GDate::operator==(const GDate &d) const
{
	if (this->_tm->tm_mday != d._tm->tm_mday)
		return (false);
	if (this->_tm->tm_mon != d._tm->tm_mon)
		return (false);
	if (this->_tm->tm_year != d._tm->tm_year)
		return (false);
	return (true);
}
bool		GDate::operator>(const GDate &d) const
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
	return (false);
}
bool		GDate::operator>=(const GDate &d) const
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
	return (true);
}
unsigned int	GDate::GetTimeStamp(void) const
{
	return ((unsigned int)mktime(this->_tm));
}

