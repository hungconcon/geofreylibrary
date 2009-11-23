
#include "GISocket.h"

int			GISocket::Send(GISocket *Socket, const GString &ToSend)
{
	if (Socket)
		return (Socket->Send(ToSend));
	return (0);
}

int			GISocket::Send(GISocket *Socket, void *Data, unsigned int Size)
{
	if (Socket && Size && Data)
		return (Socket->Send(Data, Size));
	return (0);
}

GString		GISocket::Receive(GISocket *Socket)
{
	if (Socket)
		return (Socket->Receive());
	return ("");
}

void		GISocket::Receive(GISocket *Socket, void *Data, unsigned int Size)
{
	if (Socket && Data && Size)
		Socket->Receive(Data, Size);
}

void		GISocket::Close(GISocket *Socket)
{
	if (Socket)
		Socket->Close();
}