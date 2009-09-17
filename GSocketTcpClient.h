
#ifndef __GSOCKETTCPCLIENT_H__
# define __GSOCKETTCPCLIENT_H__

#include "GString.h"
#include "GException.h"
#include "GDeclaration.h"
#include "GWarning.h"
#include "GStream.h"
#include "GExport.h"

#if defined (GWIN)
#		include "windows.h"
#ifndef WSOC
# define WSOC
#		include "Winsock2.h"
#endif
typedef int				socklen_t;
typedef SOCKET			GSocket;
#pragma comment(lib, "ws2_32.lib")
#else
#		include <sys/types.h>
#		include <sys/socket.h>
#		include <netdb.h>
#		include <netinet/in.h>
#		include <arpa/inet.h>
#		define INVALID_SOCKET	-1
#		define SOCKET_ERROR		-1
typedef	unsigned int	GSocket;
#endif

class GEXPORTED GSocketTcpClient : public GStream
{
	public:
		GSocketTcpClient(void);
		GSocketTcpClient(const GString &Ip, unsigned int Port);
		~GSocketTcpClient(void);

		int				Send(const GString &);
		int				Send(void *, unsigned int);
		GString			Receive(void);
		void			Receive(void *, unsigned int);
		GSocket			GetSocket(void) const;
		void			Init(void);
		void			Init(const GString &Ip, unsigned int Port);
		void			Connect(void);
		int				GetLastError(void) const;

		enum Error
		{	
			NONE			= 1,
			UNKNOW_HOST		= 2,
			ERROR_CONNECT	= 3,
			ERROR_SEND		= 4,
			ERROR_RECEIVE	= 5,
			ERROR_SOCKET	= 6
		};
		
	private:
		bool			_init;
		GString			_ip;
		unsigned int	_port;
		GSocket			_socket;
		sockaddr_in		_sockaddr;
		Error			_lastError;
};

#endif
