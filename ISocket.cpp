
#include "ISocket.h"

int			ISocket::Send(ISocket *Socket, const GString &ToSend)
{
	if (Socket)
		return (Socket->Send(ToSend));
	return (0);
}

int			ISocket::Send(ISocket *Socket, void *Data, unsigned int Size)
{
	if (Socket && Size && Data)
		return (Socket->Send(Data, Size));
	return (0);
}

GString		ISocket::Receive(ISocket *Socket)
{
	if (Socket)
		return (Socket->Receive());
	return ("");
}

void		ISocket::Receive(ISocket *Socket, void *Data, unsigned int Size)
{
	if (Socket && Data && Size)
		Socket->Receive(Data, Size);
}

GString		ISocket::GetIp(ISocket *Socket)
{
	if (Socket)
		return (Socket->GetIp(Socket->GetSocket()));
	return ("");
}
