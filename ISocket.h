
#ifndef __ISOCKET_H__
# define __ISOCKET_H__

#include "GString.h"

#if defined (WIN32) | defined (_WIN32) |  defined (__WIN32) | defined (WIN64) | defined (_WIN64) | defined (__WIN64)
typedef	SOCKET				GSocket;
#else
typedef	unsigned int		GSocket;
#endif

class	ISocket
{
	public:
		virtual ~ISocket(void){};
		
		virtual int					Send(GSocket Socket, const GString &ToSend) = 0;
		virtual GString				Receive(GSocket Socket) = 0;
		virtual GSocket				GetSocket(void) const = 0;
		virtual GSocket				Accept(void) = 0;
		virtual int					GetLastError(void) const = 0;
		virtual GString				GetIp(const GSocket &Socket) = 0;
		virtual GString				GetLastIp(void) const = 0;

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