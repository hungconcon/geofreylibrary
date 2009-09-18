
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
		void	AddRecipient(const GString &Mail);
		void	AddRecipients(const GStringList &List);
		void	DeleteRecipient(const GString &Mail);
		void	SetSMTP(const GString &SMTP, unsigned int Port = 25);
		void	Send(void);

	private:
		GSocketTcpClient	*_socket;
		GStringList			_listSend;
		GString				_subject;
		GString				_from;
		GString				_serveur;
		unsigned int		_port;
			
};

#endif
