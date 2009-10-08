
#ifndef		__GISOCKETCLIENT_H__
# define	__GISOCKETCLIENT_H__

#include "GString.h"
#include "GExport.h"
#include "GISocket.h"

class	GEXPORTED GISocketClient : public GISocket
{
	public:
		virtual ~GISocketClient(void){};
		
		virtual GSocket			GetSocket(void) const = 0;
		virtual void			Init(void) = 0;
		virtual void			Init(const GString &Ip, unsigned int Port) = 0;
		virtual void			Connect(void) = 0;
		virtual int				GetLastError(void) const = 0;

		enum Error
		{	
			NONE			= 1,
			UNKNOW_HOST		= 2,
			ERROR_CONNECT	= 3,
			ERROR_SEND		= 4,
			ERROR_RECEIVE	= 5,
			ERROR_SOCKET	= 6
		};

};

#endif
