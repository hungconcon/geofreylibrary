
#include "GSqlDatabase.h"

GSqlDatabase::GSqlDatabase(void)
{
	this->_socket = NULL;	
}

GSqlDatabase::~GSqlDatabase(void)
{

}

void	GSqlDatabase::Connect(const GString &host, const GString &, const GString &)
{
	this->_socket = new GSocketTcpClient(host, 80);
	//GString t = this->_socket->Receive();
	
}

void	GSqlDatabase::SelectDatabase(const GString &)
{
	
}
