
#ifndef		__ISOCKET_H__
# define	__ISOCKET_H__

#include "GString.h"
#include "GExport.h"

#if defined (GWIN)
typedef	SOCKET				GSocket;
#else
typedef	unsigned int		GSocket;
#endif

class	GEXPORTED ISocket
{
	public:
		virtual ~ISocket(void){};
		
		virtual int					Send(const GString &) = 0;
		virtual int					Send(void *Data, unsigned int Size) = 0;
				int					Send(ISocket *Socket, const GString &ToSend);
				int					Send(ISocket *Socket, void *Data, unsigned int Size);

		virtual GString				Receive(void) = 0;
				GString				Receive(ISocket *Socket);
		virtual void				Receive(void *Data, unsigned int Size) = 0;
				void				Receive(ISocket *Socket, void *Data, unsigned int Size);

		virtual GSocket				GetSocket(void) const = 0;
		virtual ISocket				*Accept(void) = 0;

		virtual int					GetLastError(void) const = 0;
				GString				GetIp(ISocket *);
		virtual GString				GetIp(const GSocket &Socket) = 0;
		virtual GString				GetLastIp(void) const = 0;
		virtual void				ClearDisconnectedSocket(void);

		enum Error
		{
			NONE			= 1,
			ERROR_INIT,
			ERROR_LISTEN	= 2,
			ERROR_BIND		= 3,
			ERROR_ACCEPT	= 4,
			ERROR_SEND		= 5,
			ERROR_RECEIVE	= 6
		};
};

#endif
