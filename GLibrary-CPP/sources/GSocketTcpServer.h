
#ifndef __GSOCKETTCPSERVER_H__
# define __GSOCKETTCPSERVER_H__

#include "GString.h"
#include "GException.h"
#include "G.h"
#include "GWarning.h"
#include "GStream.h"
#include "GExport.h"
#include "GMap.hpp"
#include "GISocketServer.h"

class	GEXPORTED GSocketTcpServer : public GISocketServer, public GStream
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
		GISocket			*Accept(void);
		void				Close(void);
		GString				GetLastIp(void) const;
		GString				GetIp(const GSocket &);
		int					GetLastError(void) const;
		void				ClearDisconnectedSocket(void);

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
