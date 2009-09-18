
#ifndef __GTIME_H__
# define __GTIME_H__

#include <time.h>
#include <stdlib.h>

#include "GDeclaration.h"
#include "GString.h"
#include "GExport.h"
#include "GPrecisionTime.h"

class GEXPORTED GTime
{
	public:
		GTime(void);
		GTime(const GPrecisionTime &);
		GTime(const GTime &Time);
		GTime(int Hours, int Minutes, int Scondes);
		~GTime(void);
	
		int			Min(void) const;
		int			Hour(void) const;
		int			Sec(void) const;
		void		AddHours(int Hours);
		void		AddMins(int Minutes);
		void		AddSecs(int Seconds);
		void		SetTime(int Hours, int Minutes, int Seconds);
		GString		GetTime(const GString &Time);
		bool		operator!=(const GTime &Time) const;
		bool		operator<(const GTime &Time) const;
		bool		operator<=(const GTime &Time) const;
		bool		operator==(const GTime &Time) const;
		bool		operator>(const GTime &Time) const;
		bool		operator>=(const GTime &Time) const;
	
	private:
		struct tm	*_tm;
};

#endif
