
#ifndef		__ISOCKETSERVER_H__
# define	__ISOCKETSERVER_H__

#include "GString.h"
#include "GExport.h"
#include "GISocket.h"

class	GEXPORTED GISocketServer : public GISocket
{
	public:
		virtual ~GISocketServer(void){};
		
		virtual GISocket				*Accept(void) = 0;

		virtual int					GetLastError(void) const = 0;
		virtual GString				GetIp(const GSocket &Socket) = 0;
		virtual GString				GetLastIp(void) const = 0;
		virtual void				ClearDisconnectedSocket(void) = 0;
		
		static	GString				GetIp(GISocketServer *);

		enum Error
		{
			NONE			= 1,
			ERROR_LISTEN	= 2,
			ERROR_BIND		= 3,
			ERROR_ACCEPT	= 4,
			ERROR_SEND		= 5,
			ERROR_RECEIVE	= 6
		};
};

#endif
