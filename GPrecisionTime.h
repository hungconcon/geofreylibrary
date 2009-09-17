#ifndef		__GPRECISIONTIME_H_
# define	__GPRECISIONTIME_H_

# include "GExport.h"
# include "GTimeOfDay.h"

# include <iostream>

class	GEXPORTED GPrecisionTime
{
public:
	GPrecisionTime(void);
	GPrecisionTime(const GPrecisionTime &);
	GPrecisionTime(struct timeval);
#ifdef _TIME64_T
	GPrecisionTime(struct timeval64);
#endif
	~GPrecisionTime(void);
	GPrecisionTime			Now(void);
	struct timeval			GetTimeval(void);
#ifdef _TIME64_T
	struct timeval64		GetTimeval64(void);
#endif
	GPrecisionTime			SetTime(const GPrecisionTime &);
	bool					operator<(const GPrecisionTime &) const;
	bool					operator==(const GPrecisionTime &) const;
	GPrecisionTime			operator-(const GPrecisionTime &) const;
	GPrecisionTime			operator+(const GPrecisionTime &) const;
	GPrecisionTime			&operator=(const GPrecisionTime &);
	static	GPrecisionTime	Null(void);

	friend std::ostream &operator<<(std::ostream &, const GPrecisionTime &);

private:
#ifdef _TIME64_T
	struct timeval64		_now;
#else
	struct timeval			_now;
#endif
};

#endif
