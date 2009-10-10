using System;

namespace G
{
    public class GDateTime
    {
        DateTime    _time;

        public              GDateTime(Int64 timestamp)
        {
            this._time = new DateTime(timestamp);
        }
        public              GDateTime(DateTime d)
        {
            this._time = d;
        }
        public              GDateTime()
        {
            this._time = DateTime.Now;
        }
        public              GDateTime(GDateTime d)
        {
            this._time = d._time;
        }
        public              GDateTime(int y, int M, int d, int h, int m, int s)
        {
            this._time = new DateTime(y, M, d, h, m, s);
        }
        public int          Hour()
        {
            return (this._time.Hour);
        }
        public int          Minute()
        {
	        return (this._time.Minute);
        }
        public int          Second()
        {
	        return (this._time.Second);
        }
        public void         AddHours(int h)
        {
	        this._time.AddHours(h);
        }
        public void         AddMinutes(int m)
        {
	        this._time.AddMinutes(m);
        }
        public void         AddSeconds(int s)
        {
	        this._time.AddSeconds(s);
        }
        public Int32          Day()
        {
	        return (this._time.Day);
        }
        public Int32          Month()
        {
            return (this._time.Month);
        }
        public Int32          Year()
        {
            return (this._time.Year);
        }
        public Int32         DayOfYear()
        {
	        return (this._time.DayOfYear);
        }
        public bool         IsBisextile()
        {
            return (DateTime.IsLeapYear(this._time.Year));
        }
        public static bool  IsBisextile(int Year)
        {
            return (DateTime.IsLeapYear(Year));
        }
        public void         AddYears(int y)
        {
            this._time.AddYears(y);
        }
        public void         AddMonths(int m)
        {
            this._time.AddMonths(m);
        }
        public void         AddDays(int d)
        {
	        this._time.AddDays(d);
        }
        public int          GetNumberDayMonth()
        {
            switch (this._time.Month) 
	        {
		    case 1 : case 3 : case 5: case 7 : case 8 : case 10 : case 12 :
			    return (31);
		    case 4 : case 6 : case 9 : case 11 :
			    return (30);
		    case 2 :
			    return (this.IsBisextile()) ? 29 : 28;
	        }
	        return (0);
        }
        public void         SetDate(int y, int m, int d)
        {
            this._time = new DateTime(y, m, d);
        }
        public void         SetTime(int h, int m, int s)
        {
            new DateTime(this._time.Year, this._time.Month, this._time.Day, h, m, s);
        }
        public static int   GetNumberDayMonth(int m, int y)
        {
	        switch (m) 
	        {
		        case 1 : case 3 : case 5: case 7 : case 8 : case 10 : case 12 :
			        return (31);
		        case 4 : case 6 : case 9 : case 11 :
			        return (30);
		        case 2 :
			        return (GDateTime.IsBisextile(y)) ? 29 : 28;
	        }
	        return 0;
        }
        public GString      GetDateTime(GString Format)
        {
	        GString test = new GString(this._time.Day);
	        //DayInterface *d = GDayInstance::GetInstance(op);
	        //g = g.Replace("%dddd", d->GetDay(this._tm->tm_wday));
	        //g = g.Replace("%ddd", d->GetTruncateDay(this._tm->tm_wday));
	        Format = Format.Replace("%dd", test.RightJustified(2, '0'));
	        Format = Format.Replace("%d", test);
	        //MonthInterface *m = GMonthInstance::GetInstance(op);
	        test = new GString(this._time.Month);
	        //Format = Format.Replace("%MMMM", m->GetMonth(this._tm->tm_mon));
	        //Format = Format.Replace("%MMM", m->GetTruncateMonth(this._tm->tm_mon));
	        Format = Format.Replace("%MM", test.RightJustified(2, '0'));
	        Format = Format.Replace("%M", test);
	        test = new GString(this._time.Year);
	        Format = Format.Replace("%yyyy", test);
	        Format = Format.Replace("%yy", test.Substr(2, 4));
	        test = new GString(this._time.Hour);
	        Format = Format.Replace("%hh", test.RightJustified(2, '0'));
	        Format = Format.Replace("%h", test);
	        test = new GString (this._time.Minute);
	        Format = Format.Replace("%mm", test.RightJustified(2, '0'));
	        Format = Format.Replace("%m", test);
	        test = new GString (this._time.Second);
	        Format = Format.Replace("%ss", test.RightJustified(2, '0'));
	        Format = Format.Replace("%s", test);
	        return (Format);
        }
 
        public static bool		operator !=(GDateTime d1, GDateTime d2)
        {
            if (d1._time != d2._time)
                return (true);
            return (false);
        }

        public static bool		operator <(GDateTime d1, GDateTime d2)
        {
            if (d1._time < d2._time)
                return (true);
            return (false);
        }
        public static bool      operator<=(GDateTime d1, GDateTime d2)
        {
            if (d1._time <= d2._time)
                return (true);
            return (false);
        }
        public static bool      operator==(GDateTime d1, GDateTime d2)
        {
            if (d1._time == d2._time)
                return (true);
            return (false);
        }
        public static bool      operator>(GDateTime d1, GDateTime d2)
        {
            if (d1._time > d2._time)
                return (true);
            return (false);
        }
        public static bool operator >=(GDateTime d1, GDateTime d2)
        {
            if (d1._time >= d2._time)
                return (true);
            return (false);
        }
        public Int64              GetTimeStamp()
        {
            return (this._time.Ticks);
        }
    }
}