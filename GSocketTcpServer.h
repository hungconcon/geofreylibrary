
#ifndef __GSOCKETTCPSERVER_H__
# define __GSOCKETTCPSERVER_H__

#include "GString.h"
#include "GException.h"
#include "GDeclaration.h"
#include "GWarning.h"
#include "GStream.h"
#include "GExport.h"
#include "GMap.hpp"

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

class GEXPORTED GSocketTcpServer : public GStream
{
	public:
		GSocketTcpServer(unsigned int Port = 12345, unsigned int NbConnexion = 100);
		~GSocketTcpServer(void);

		static int			Send(GSocket Socket, const GString &ToSend);
		static int			Send(GSocket Socket, void *Data, unsigned int Size);
		int					Send(const GString &ToSend);
		GString				Receive(void);
		static GString		Receive(GSocket Socket);
		static void			Receive(GSocket Socket, void *Data, unsigned int Size);
		GSocket				GetSocket(void) const;
		GSocket				Accept(void);
		int					GetLastError(void) const;
		GString				GetLastIp(void) const;
		GString				GetIp(const GSocket &Socket) const;
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
