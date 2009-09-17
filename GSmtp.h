
#ifndef __GSMTP_H__
# define __GSMTP_H__

#include "GString.h"
#include "GSocketTcpClient.h"

class GSmtp
{
	public:
		GSmtp(const GString &, unsigned int port = 25);
		~GSmtp(void);
		
		void	SetSubject(const GString &Subject);
		void	SetSender(const GString &Sender);

	private:
		GSocketTcpClient	*_socket;
		GStringList			_listSend;
		GString				_subject;
		GString				_from;
};

#endif
