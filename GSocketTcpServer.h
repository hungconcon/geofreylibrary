
#ifndef __GSOCKETTCPSERVER_H__
# define __GSOCKETTCPSERVER_H__

#include "GString.h"
#include "GException.h"
#include "GDeclaration.h"
#include "GWarning.h"
#include "GStream.h"
#include "GExport.h"
#include "GMap.hpp"
#include "ISocket.h"

#if defined (GWIN)
#		include "windows.h"
#		include "Winsock2.h"
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

class GEXPORTED GSocketTcpServer : public ISocket, public GStream
{
	public:
		GSocketTcpServer(unsigned int Port = 12345, unsigned int NbConnexion = 100);
		GSocketTcpServer(unsigned int Port, unsigned int NbConnexion, GSocket Sock);
		~GSocketTcpServer(void);

		int					Send(const GString &ToSend);
		int					Send(void *Data, unsigned int Size);

		GString				Receive(void);
		void				Receive(void *Data, unsigned int Size);

		GSocket				GetSocket(void) const;
		ISocket				*Accept(void);

		GString				GetLastIp(void) const;
		GString				GetIp(const GSocket &);
		int					GetLastError(void) const;
		void				ClearDisconnectedSocket(void);

		enum Error
		{
			NONE			= 1,
			ERROR_LISTEN	= 2,
			ERROR_BIND		= 3,
			ERROR_ACCEPT	= 4,
			ERROR_SEND		= 5,
			ERROR_RECEIVE	= 6
		};



	private:
		GString					_ip;
		unsigned int			_port;
		unsigned int			_maxConnexion;
		GSocket					_socket;
		GString					_lastIp;
		sockaddr_in				_sockaddr;
		GMap<GSocket, GString>	_map;
		Error					_lastError;
};

#endif
