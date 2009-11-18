
#ifndef __GSOCKETSELECTOR_H__
# define __GSOCKETSELECTOR_H__

#include "GExport.h"
#include "GISocket.h"
#include "GVector.hpp"

typedef GVector<GISocket *> GSocketList;

class GEXPORTED GSocketSelector
{
	public:
		GSocketSelector(void);
		~GSocketSelector(void);

		void		SetTimeOut(unsigned int MilliSecond);
		void		Select(void);
		GSocketList	GetSocketRead(void) const;
		GSocketList	GetSocketWrite(void) const;
		void		AddRead(GISocket *);
		void		AddRead(GVector<GISocket *>);
		void		AddWrite(GISocket *);
		void		AddWrite(GVector<GISocket *>);
		bool		IsSetRead(GISocket *);
		bool		IsSetWrite(GISocket *);

	private:
		GSocketList		_rw;
		GSocketList		_write;
		GSocketList		_read;
		fd_set			_fdRead;
		fd_set			_fdWrite;
		timeval			_tv;
		unsigned int	_max;
		bool			_timeOut;
};


#endif