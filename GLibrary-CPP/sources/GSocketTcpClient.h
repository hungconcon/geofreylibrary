
#ifndef __GSOCKETTCPCLIENT_H__
# define __GSOCKETTCPCLIENT_H__

#include "GString.h"
#include "GException.h"
#include "G.h"
#include "GWarning.h"
#include "GStream.h"
#include "GExport.h"
#include "GISocketClient.h"

class	GEXPORTED GSocketTcpClient : public GISocketClient, public GStream
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
		void			Close(void);

	private:
		bool			_init;
		GString			_ip;
		unsigned int	_port;
		GSocket			_socket;
		sockaddr_in		_sockaddr;
		Error			_lastError;
};

#endif
