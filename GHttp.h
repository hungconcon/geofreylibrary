
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
	
		void		SetUser(const GString &, const GString &);
		void		SetProxy(const GString &, unsigned int port);
		void		SetProxy(const GString &, unsigned int port, const GString &, const GString &);
		GString	Get(const GString &);
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
