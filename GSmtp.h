
#ifndef __GSMTP_H__
# define __GSMTP_H__

#include "GString.h"
#include "GSocketTcpClient.h"

class GSmtp
{
	public:
		GSmtp(const GString &, unsigned int port = 25);
		~GSmtp(void);

	private:
		GSocketTcpClient	*_socket;
};

#endif
