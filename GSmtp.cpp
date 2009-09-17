
#include "GSmtp.h"

GSmtp::GSmtp(const GString &ip, unsigned int port)
{
	this->_socket = new GSocketTcpClient(ip, port);
	this->_socket->Connect();

}

GSmtp::~GSmtp(void)
{

}

void	GSmtp::SetSubject(const GString &Subject)
{
	this->_subject = Subject;
}

void	GSmtp::SetSender(const GString &E)
{
	this->_from = E;
}