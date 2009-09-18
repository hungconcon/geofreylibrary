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
	GPrecisionTime(struct timeval64);
	~GPrecisionTime(void);
	GPrecisionTime			Now(void);
	struct timeval			GetTimeval(void) const;
	struct timeval64		GetTimeval64(void) const;
	GPrecisionTime			SetTime(const GPrecisionTime &);
	bool					operator<(const GPrecisionTime &) const;
	bool					operator==(const GPrecisionTime &) const;
	GPrecisionTime			operator-(const GPrecisionTime &) const;
	GPrecisionTime			operator+(const GPrecisionTime &) const;
	GPrecisionTime			&operator=(const GPrecisionTime &);
	static	GPrecisionTime	Null(void);

	friend std::ostream &operator<<(std::ostream &, const GPrecisionTime &);

private:
	struct timeval64		_now;
};

#endif
