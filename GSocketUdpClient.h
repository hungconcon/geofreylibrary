
#ifndef		__GSOCKETUDPCLIENT_H__
# define	__GSOCKETUDPCLIENT_H__

#include "GString.h"
#include "GException.h"
#include "GDeclaration.h"
#include "GWarning.h"
#include "GStream.h"
#include "GExport.h"
#include "GISocketClient.h"

class	GEXPORTED GSocketUdpClient : public GISocketClient, public GStream
{
	public:
		GSocketUdpClient(void);
		GSocketUdpClient(const GString &Ip, unsigned int Port);
		~GSocketUdpClient(void);

		int				Send(const GString &);
		int				Send(void *, unsigned int);

		GString			Receive(void);
		void			Receive(void *, unsigned int);
		
		GSocket			GetSocket(void) const;
		void			Init(void);
		void			Init(const GString &Ip, unsigned int Port);
		void			Connect(void);
		int				GetLastError(void) const;

	private:
		bool			_init;
		GString			_ip;
		unsigned int	_port;
		GSocket			_socket;
		sockaddr_in		_sockaddr;
		Error			_lastError;
};

#endif
