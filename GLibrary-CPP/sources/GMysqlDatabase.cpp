
#include "GMysqlDatabase.h"

GMysqlDatabase::GMysqlDatabase(void)
{

}

GMysqlDatabase::~GMysqlDatabase(void)
{

}

GString		GMysqlDatabase::PacketRecuperation(void)
{
	this->_receive += this->_socket.Receive();
	if (this->_receive.Size() > 4)
	{ 
		unsigned int PacketSize = this->_receive[0] + this->_receive[1] * GAlgo::Pow(2, 8) + this->_receive[2] * GAlgo::Pow(2, 16);
		if (this->_receive.Size() >= 4 + PacketSize)
		{
			GString Current = this->_receive.Substr(4, 4 + PacketSize);
			this->_receive = this->_receive.Substr(4 + 1 + PacketSize);
			return (Current);
		}
	}
	return ("");
}

void		GMysqlDatabase::MakePacket(const GString &Packet)
{
	int size = Packet.Size();
	char *h = new char[4];
	h[3] = 0;
	h[2] = (char)(size / GAlgo::Pow(2, 16)); 
	int temp = size - h[2] * GAlgo::Pow(2, 16);
	h[1] = (char)(temp / GAlgo::Pow(2, 8));
	temp -= h[1] * GAlgo::Pow(2, 8);
	h[0] = (char)temp;
	GString p = GString::GetBuffer(h, 4) + Packet;
	delete[] h;
	this->_socket.Send(p);
}

void		GMysqlDatabase::ParseInitialHandShake(const GString &Packet)
{
	this->_protocolVersion = Packet[0];
	unsigned int i = 1;
	while (Packet[i])
		++i;
	this->_serverVersion = Packet.Substr(1, i);
	this->_serveurCapabilities = Packet.Substr(i + 4 + 8 + 1 + 1, i + 4 + 8 + 1 + 2);
	this->_scrambleBuffer = Packet.Substr(i + 4, i + 4 + 8);
}

void		GMysqlDatabase::Authentification(void)
{
	GString Paquet;
	char *test = new char[];
	

	
}

GString		GMysqlDatabase::GetServerVersion(void) const
{
	return (this->_serverVersion);
}

bool		GMysqlDatabase::Connect(const GString &Host, const GString &Login, const GString &Database, const GString &Pass, unsigned int Port)
{
	try
	{
		this->_login = Login;
		this->_pass = Pass;
		this->_socket.Init(Host, Port);
		this->_socket.Connect();
		GString current = this->PacketRecuperation();
		this->ParseInitialHandShake(current);
		this->Authentification();
		return (true);
	}
	catch (GException g)
	{
		std::cout << g.what() << std::endl;		
	}
	return (false);
}