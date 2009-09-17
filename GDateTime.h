
#ifndef __GDATETIME_H__
# define __GDATETIME_H__

#include "GString.h"
#include "GDate.h"
#include "GTime.h"
#include "GExport.h"
#include "GDayInstance.h"

class GEXPORTED GDateTime
{
	public:
		GDateTime(void);
		GDateTime(const GDate &Date);
		GDateTime(const GTime &Time);
		GDateTime(const GDate &Date, const GTime &Time);
		GDateTime(int Year, int Month, int Day, int Hour = 0, int Minutes = 0, int Seconds = 0);
		~GDateTime(void);

		int				Min(void) const;
		int				Hour(void) const;
		int				Sec(void) const;
		void			AddHours(int Hours);
		void			AddMins(int Minutes);
		void			AddSecs(int Seconds);
		void			SetTime(int Hours, int Minutes, int Seconds);
		GString			GetDateTime(const GString &Format, G::LanguageOption op = G::FRENCH);
		int				Day(void) const;
		int				Month(void) const;
		int				Year(void) const;
		int				DayYear(void) const;
		int				DayWeek(void) const;
		bool			IsBisextile(void) const;
		int				GetNumberDayMonth(void) const;
		void			AddYears(int);
		void			AddMonths(int);
		void			AddDays(int);
		void			SetDate(int Year, int Month, int Day);
		static int		GetNumberDayMonth(int Month, int Year);
		static bool		IsBisextile(int);
		GString			GetDate(const GString &Format, G::LanguageOption Language = G::FRENCH);
		unsigned int	GetTimeStamp(void) const;



		bool		operator!=(const GDateTime &DateTime) const;
		bool		operator<(const GDateTime &DateTime) const;
		bool		operator<=(const GDateTime &DateTime) const;
		bool		operator==(const GDateTime &DateTime) const;
		bool		operator>(const GDateTime &DateTime) const;
		bool		operator>=(const GDateTime &DateTime) const;

	private:
		struct tm	*_tm;
};

#endif
