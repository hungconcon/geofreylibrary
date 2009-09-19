
#include "GISocketServer.h"

GString		GISocketServer::GetIp(GISocketServer *Socket)
{
	if (Socket)
		return (Socket->GetIp(Socket->GetSocket()));
	return ("");
}
