
#ifndef __GDATE_H__
# define __GDATE_H__

#include <stdlib.h>
#include <time.h>
#include "G.h"
#include "GString.h"
#include "GDayInstance.h"
#include "GMonthInstance.h"
#include "GExport.h"

class GEXPORTED GDate
{
	public:
		GDate(void);
		GDate(const GDate &Date);
		GDate(int Year, int Month, int Day);
		~GDate(void);
	
		int			Day(void) const;
		int			Month(void) const;
		int			Year(void) const;
		int			DayYear(void) const;
		int			DayWeek(void) const;
		bool		IsBisextile(void) const;
		int			GetNumberDayMonth(void) const;
		void		AddYears(int);
		void		AddMonths(int);
		void		AddDays(int);
		void		SetDate(int Year, int Month, int Day);
		static int	GetNumberDayMonth(int Month, int Year);
		static bool	IsBisextile(int);
		GString		GetDate(const GString &Format, G::LanguageOption Language = G::FRENCH);
		bool		operator!=(const GDate &Date) const;
		bool		operator<(const GDate &Date) const;
		bool		operator<=(const GDate &Date) const;
		bool		operator==(const GDate &Date) const;
		bool		operator>(const GDate &Date) const;
		bool		operator>=(const GDate &Date) const;
		unsigned int	GetTimeStamp(void) const;

	private:
		struct tm	*_tm;
};

#endif
