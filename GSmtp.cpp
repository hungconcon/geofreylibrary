
#include "GSmtp.h"

GSmtp::GSmtp(const GString &ip, unsigned int port)
{
	this->_socket = new GSocketTcpClient(ip, port);
	this->_socket->Connect();

}

GSmtp::~GSmtp(void)
{

}

void	GSmtp::SetSMTP(const GString &SMTP, unsigned int Port)
{
	this->_serveur = SMTP;
	this->_port = Port;
}

void	GSmtp::AddRecipient(const GString &Mail)
{
	this->_listSend.PushBack(Mail);
}

void	GSmtp::AddRecipients(const GStringList &list)
{
	//this->_listSend.PushBack(list);
}


void	GSmtp::DeleteRecipient(const GString &Mail)
{
	this->_listSend.Delete(Mail);
}

void	GSmtp::SetSubject(const GString &Subject)
{
	this->_subject = Subject;
}

void	GSmtp::SetSender(const GString &E)
{
	this->_from = E;
}

void	GSmtp::Send(void)
{

}