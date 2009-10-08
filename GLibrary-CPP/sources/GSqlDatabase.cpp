
#include "GSqlDatabase.h"

GSqlDatabase::GSqlDatabase(void)
{

}

GSqlDatabase::~GSqlDatabase(void)
{

}

void	GSqlDatabase::Connect(const GString &Host, const GString &Login, const GString &Pass)
{
	this->_socket.Init(Host, 3306);
	this->_socket.Connect();
	GString t = this->_socket.Receive();
	for (unsigned int i = 0; i < t.Size(); ++i)
	{
		std::cout << t[i];
	}
	std::cout << t.Find("5.1") << std::endl;
	std::cout << std::endl;
}

void	GSqlDatabase::SelectDatabase(const GString &)
{
	
}
