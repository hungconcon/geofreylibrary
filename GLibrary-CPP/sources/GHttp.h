
#ifndef __GHTTP_H__
# define __GHTTP_H__

#include "GString.h"
#include "GThread.h"
#include "GMutex.h"
#include "GExport.h"
#include "GSocketTcpClient.h"
#include "GCryptography.h"

class GEXPORTED GHttp
{
	public:
		GHttp(const GString &, unsigned int port = 80);
		~GHttp(void);
	
		void		SetUser(const GString &Login, const GString &Password);
		void		SetProxy(const GString &Server, unsigned int Port);
		void		SetProxy(const GString &Server, unsigned int Port, const GString &Login, const GString &Password);
		GString		Get(const GString &);
		void		Post(const GString &, const GString &);

	private:
		GString				_host;
		GString				_user;
		GString				_pass;
		unsigned int		_port;
		GString				_proxyHost;
		unsigned int		_proxyPort;
		GString				_proxyUser;
		GString				_proxyPass;
		GSocketTcpClient	_socket;
		
};

#endif
