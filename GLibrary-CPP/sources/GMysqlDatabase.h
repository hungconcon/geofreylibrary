
#ifndef __GMYSQLDATABASE_H__
# define __GMYSQLDATABASE_H__

#include "GExport.h"
#include "GISqlDatabase.h"
#include "GAlgo.h"

class GEXPORTED GMysqlDatabase //: public GISqlDatabase
{
	public:
		GMysqlDatabase(void);
		~GMysqlDatabase(void);

		bool			Connect(const GString &Host, const GString &Login, const GString &Database, const GString &Pass = "", unsigned int Port = 3306);
		GString			GetServerVersion(void) const;

	private:
		void	ParseInitialHandShake(const GString &Packet);
		void	Authentification(void);
		void	MakePacket(const GString &Packet);

		GString	PacketRecuperation(void);
		
		


	private:
		GSocketTcpClient	_socket;
		GString				_receive;
		char				_protocolVersion;
		GString				_serveurCapabilities;
		unsigned int		_threadId;
		GString				_serverVersion;
		GString				_login;
		GString				_pass;
		GString				_scrambleBuffer;
};

#endif