
#ifndef __GSMTP_H__
# define __GSMTP_H__

#include "GString.h"
#include "GSocketTcpClient.h"

class GSmtp
{
	public:
		GSmtp(const GString &, unsigned int port = 25);
		GSmtp(void);
		~GSmtp(void);
		
		void	SetSubject(const GString &Subject);
		void	SetSender(const GString &Sender);
		void	SetSender(const GString &Mail, const GString &Name);
		void	AddRecipient(const GString &Mail);
		void	AddRecipient(const GString &Mail, const GString &Name);
		void	DeleteRecipient(const GString &Mail);
		void	SetServer(const GString &Server, unsigned int Port = 25);
		void	Send(void);
		void	SavePacketsInFile(const GString &FileName);
		GString	GetPackets(void);

	private:
		void	MakeMap(void);
		void	CheckError(const GString &);
		GSocketTcpClient	_socket;
		GStringList			_listSend;
		GString				_subject;
		GString				_from;
		GString				_fromName;
		GString				_serveur;
		GString				_packets;
		unsigned int		_port;
		GStringMap			_map;
			
};

#endif
