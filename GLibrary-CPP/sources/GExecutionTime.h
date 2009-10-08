#ifndef		__GEXECUTIONTIME_H__
# define	__GEXECUTIONTIME_H__

# include "GExport.h"
# include "GPrecisionTime.h"

class	GEXPORTED GExecutionTime
{
public:
	GExecutionTime(void);
	~GExecutionTime(void);
	void			Start(void);
	GPrecisionTime	Now(void);
	GPrecisionTime	Stop(void);
	GPrecisionTime	Restart(void);

private:
	bool			_started;
	GPrecisionTime	_begin;
};

#endif
