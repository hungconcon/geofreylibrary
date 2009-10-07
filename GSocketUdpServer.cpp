
#include "GSocketUdpServer.h"

GSocketUdpServer::GSocketUdpServer(unsigned int port, unsigned int maxConnexion)
{
	this->_port = port;
	this->_maxConnexion = maxConnexion;
#if defined (GWIN)
	WSADATA	wsaData;
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != NO_ERROR)
	{
		GWarning::Warning("GSocketUdpServer", "GSocketUdpServer(unsigned int port, unsigned int max)", "Error WSAStartup()");
		throw GException("GSocketUdpServer", "Error WSAStartup() !");
	}
	this->_socket = WSASocket(AF_INET, SOCK_DGRAM, 0, 0, 0, 0);
	if (this->_socket == INVALID_SOCKET)
	{
		GWarning::Warning("GSocketTcpServer", "GSocketTcpServer(unsigned int port, unsigned int max)", "Error WSASocket()");
		throw GException("GSocketUdpServer", "Error WSASocket()");
	}
	this->_sockaddr.sin_family = AF_INET;
	this->_sockaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (WSAHtons(this->_socket, this->_port, &this->_sockaddr.sin_port) == SOCKET_ERROR)
	{
		GWarning::Warning("GSocketTcpServer", "GSocketTcpServer(unsigned int port, unsigned int max)", "Error WSAHtons()");
		throw GException("GSocketUdpServer", "Error WSAHtons()");
	}
	if (WSAHtonl(this->_socket, INADDR_ANY, &this->_sockaddr.sin_addr.s_addr) == SOCKET_ERROR)
	{
		GWarning::Warning("GSocketTcpServer", "GSocketTcpServer(unsigned int port, unsigned int max)", "Error WSAHtons()");
		throw GException("GSocketTcpServer", "Error in WSAHtonl()");
	}
	sockaddr_in	s_port;
	socklen_t len = sizeof(s_port);
	if (bind(this->_socket, reinterpret_cast <sockaddr*> (&this->_sockaddr), sizeof(this->_sockaddr)) == SOCKET_ERROR) 
	{
		closesocket(this->_socket);
		throw GException("GSocketTcpServer", "bind() failed.");
	}
	if (getsockname(this->_socket, (SOCKADDR*)&s_port, &len) < 0)
	{
		closesocket(this->_socket);
		throw GException("GSocketTcpServer", "Error sockname");
	}
#else
	if ((int)(this->_socket = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
	{
		this->_lastError = GSocketUdpServer::ERROR_SOCKET;
		throw GException("GSocketUdpServer", "Error socket()");
	}
	this->_sockaddr.sin_family = AF_INET;
	this->_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	this->_sockaddr.sin_port = htons(this->_port);
	if (bind(this->_socket,(sockaddr *) &(this->_sockaddr), sizeof (this->_sockaddr)) == SOCKET_ERROR)
	{
		this->_lastError = GSocketTcpServer::ERROR_SOCKET;
		throw GException("GSocketTcpServer", "Error bind");
	}
#endif
}

GSocketUdpServer::~GSocketUdpServer(void)
{
	#if defined (GWIN)
		closesocket(this->_socket);
		WSACleanup();
	#else
		close(this->_socket);
	#endif
}

int			GSocketUdpServer::GetLastError(void) const
{
	return (this->_lastError);
}

GISocket	*GSocketUdpServer::Accept(void)
{
	return (NULL);
}

int			GSocketUdpServer::Send(const GString &s)
{
#if defined (GWIN)
	int		rc, err;
	WSABUF	DataBuf;
	DWORD	SendBytes = 0;
	DataBuf.len = s.Size();
	DataBuf.buf = s.ToChar();
	rc = WSASendTo(this->_socket, &DataBuf, 1, &SendBytes, NULL, reinterpret_cast <sockaddr*> (&this->_sockaddr), DataBuf.len, NULL, NULL);
	delete[] DataBuf.buf;
	if ((rc == SOCKET_ERROR) && (WSA_IO_PENDING != (err = WSAGetLastError())))
	{
		this->_lastError = GSocketUdpServer::ERROR_SEND;
		throw GException("GSocketUdpServer", "Error WSASend() !");
	}
	return (SendBytes);
#else
	int	l = 0;
	char	*tmp = s.ToChar();
	l = sendto(this->_socket, tmp, s.Size(), 0, 0, 0);
	delete[] tmp;
	if (l < 0)
	{
		this->_lastError = GSocketUdpServer::ERROR_SEND;
		throw GException("GSocketUdpServer", "Error send() !");
	}
	return (l);
#endif
}

int			GSocketUdpServer::Send(void *s, unsigned int size)
{
#if defined (GWIN)
	int		rc, err;
	WSABUF	DataBuf;
	DWORD	SendBytes = 0;
	DataBuf.len = size;
	DataBuf.buf = (char *)s;
	rc = WSASendTo(this->_socket, &DataBuf, 1, &SendBytes, NULL, reinterpret_cast <sockaddr*> (&this->_sockaddr), DataBuf.len, NULL, NULL);
	if ((rc == SOCKET_ERROR) && (WSA_IO_PENDING != (err = WSAGetLastError())))
	{
		this->_lastError = GSocketUdpServer::ERROR_SEND;
		throw GException("GSocketUdpServer", "Error WSASend() !");
	}
	return (SendBytes);
#else
	int	l = 0;
	l = sendto(this->_socket, s, size, 0, 0, 0);
	if (l < 0)
	{
		this->_lastError = GSocketUdpServer::ERROR_SEND;
		throw GException("GSocketUdpServer", "Error send() !");
	}
	return (l);
#endif
}

GString		GSocketUdpServer::Receive(void)
{
#if defined (GWIN)
	int		ret;
	int		len = sizeof(this->_sockaddr);
	DWORD	dwBytesRet, dwFlags;
	char	buffer[1024];
	WSABUF	wbuf;
	wbuf.len = 1024;
	wbuf.buf = buffer;
	dwFlags = 0;
	ret = WSARecvFrom(this->_socket, &wbuf, 1, &dwBytesRet, &dwFlags, reinterpret_cast <sockaddr*> (&this->_sockaddr), &len, NULL, NULL);
	if (ret == SOCKET_ERROR)
		return (GString());
	return (GString::GetBuffer(wbuf.buf, dwBytesRet));
#else
	char		buffer[1024];
	int	li = 0;
	li = recvfrom(this->_socket, buffer, sizeof(buffer), 0, 0, 0);
	if (li <= 0)
		return (GString(""));
	return (GString::GetBuffer(buffer, li));
#endif
}

void		GSocketUdpServer::Receive(void *s, unsigned int size)
{
#if defined (GWIN)
	int		ret;
	int		len = sizeof(this->_sockaddr);
	DWORD	dwBytesRet, dwFlags;
	WSABUF	wbuf;
	wbuf.len = size;
	wbuf.buf = (char *)s;
	dwFlags = 0;
	ret = WSARecvFrom(this->_socket, &wbuf, 1, &dwBytesRet, &dwFlags, reinterpret_cast <sockaddr*> (&this->_sockaddr), &len, NULL, NULL);
	if (ret == 0)
		return ;
	throw GException("GSocketUdpSever", "Error WSARecvFrom");
#else
	int	li = 0;
	li = recvfrom(this->_socket, s, size, 0, 0, 0);
	if (li <= 0)
		throw GException("GSocketUdpServer", "Error recvfrom");
#endif
}

GSocket		GSocketUdpServer::GetSocket(void) const
{
	return (this->_socket);
}

GString		GSocketUdpServer::GetLastIp(void) const
{
	return (this->_lastIp);
}

GString		GSocketUdpServer::GetIp(const GSocket &Sock)
{
	if (this->_map.ExistKey(Sock))
		return (this->_map[Sock]);
	return ("");
}

void		GSocketUdpServer::ClearDisconnectedSocket(void)
{
	for (unsigned int i = 0; i < this->_map.Size(); ++i)
	{
		if (this->_map.Key(i) == 0)
			this->_map.EraseKey(i);
	}
}
