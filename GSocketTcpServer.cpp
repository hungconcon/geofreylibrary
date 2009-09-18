
#include "GSocketTcpServer.h"

GSocketTcpServer::GSocketTcpServer(unsigned int port, unsigned int maxConnexion) : _map()
{
	this->_port = port;
	this->_maxConnexion = maxConnexion;
#if defined (GWIN)
	WSADATA			wsaData;
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != NO_ERROR)
	{
		GWarning::Warning("GSocketTcpClient", "GSocketTcpClient(const GString &IP, unsigned int Port)", "Error WSAStartup()");
		throw GException(G::SOCKET_INIT_ERROR);
	}
	this->_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
	if (this->_socket == INVALID_SOCKET)
	{
		GWarning::Warning("GSocketTcpClient", "GSocketTcpClient(const GString &IP, unsigned int Port)", "Error WSASocket()");
		throw GException(G::SOCKET_INIT_ERROR);
	}
	this->_sockaddr.sin_family = AF_INET;
	this->_sockaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (WSAHtons(this->_socket, this->_port, &this->_sockaddr.sin_port) == SOCKET_ERROR)
	{
		GWarning::Warning("GSocketTcpClient", "GSocketTcpClient(const GString &IP, unsigned int Port)", "Error WSAHtons()");
		throw GException(G::SOCKET_INIT_ERROR);
	}
	if (WSAHtonl(this->_socket, INADDR_ANY, &this->_sockaddr.sin_addr.s_addr) == SOCKET_ERROR)
		throw GException("GSocketTcpServer", "Error in WSAHtonl()");
	sockaddr_in	s_port;
	socklen_t len = sizeof(s_port);
	if (bind(this->_socket, reinterpret_cast <sockaddr*> (&this->_sockaddr), sizeof(this->_sockaddr)) == SOCKET_ERROR) 
	{
		closesocket(this->_socket);
		throw GException("GSocketTcpServer", "bind() failed.");
	}
	if (listen(this->_socket, this->_maxConnexion) == SOCKET_ERROR) 
	{
		closesocket(this->_socket);
		throw GException("GSocketTcpServer", "Error listening on socket.");
	}
	if (getsockname(this->_socket, (SOCKADDR*)&s_port, &len) < 0)
	{
		closesocket(this->_socket);
		throw GException("GSocketTcpServer", "Error sockname");
	}

#else
	if ((int)(this->_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		GWarning::Warning("GSocketTcpClient", "GSocketTcpClient(const GString &IP, unsigned int Port)", "Error socket()");
		throw GException(G::SOCKET_INIT_ERROR);
	}
	this->_sockaddr.sin_family = AF_INET;
	this->_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	this->_sockaddr.sin_port = htons(this->_port);
	if (bind(this->_socket,(sockaddr *) &(this->_sockaddr), sizeof (this->_sockaddr)) == SOCKET_ERROR)
      throw GException("GSocketTcpServer", "Error bind");
	if (listen(this->_socket, this->_maxConnexion) == SOCKET_ERROR)
		throw GException("GSocketTcpServer", "Error listen");
#endif
}

GSocketTcpServer::~GSocketTcpServer(void)
{
#if defined (GWIN)
	closesocket(this->_socket);
	WSACleanup();
#else
	close(this->_socket);
#endif
}

GSocket		GSocketTcpServer::Accept(void)
{
#if defined (GWIN)
	sockaddr_in	addr;
	int len = sizeof(addr);
	SOCKET s = WSAAccept(this->_socket, (sockaddr *)&addr, &len, NULL, NULL);
	if ((int)s == INVALID_SOCKET) 
	{
		closesocket(this->_socket);
		WSACleanup();
		throw GException("GSocketTcpServer", "Error in WSAAccept()");
		this->_lastError = GSocketTcpServer::ERROR_ACCEPT;
	}
	this->_lastIp = inet_ntoa(addr.sin_addr);
	this->_map[s] = inet_ntoa(addr.sin_addr);
	return s;
#else
	sockaddr_in	addr;
	int len = sizeof(addr);
	GSocket s = accept(this->_socket, (sockaddr *)&addr, (socklen_t *)&len);
	if ((int)s == INVALID_SOCKET) 
	{
		close(this->_socket);
		throw GException("GSocketTcpServer", "Error accept() !");
		this->_lastError = GSocketTcpServer::ERROR_ACCEPT;
	}
	this->_lastIp = inet_ntoa(addr.sin_addr);
	this->_map[s] = inet_ntoa(addr.sin_addr);
	return (s);
#endif
}



int			GSocketTcpServer::GetLastError(void) const
{
	return (this->_lastError);
}
int			GSocketTcpServer::Send(const GString &s)
{
#if defined (GWIN)
	int		rc, err;
	int		len = sizeof(this->_sockaddr);
	WSABUF	DataBuf;
	DWORD	SendBytes = 0;
	DataBuf.len = s.Size();
	DataBuf.buf = s.ToChar();
	rc = WSASend(this->_socket, &DataBuf, 1, &SendBytes, 0, NULL, NULL);
	delete[] DataBuf.buf;
	if ((rc == SOCKET_ERROR) && (WSA_IO_PENDING != (err = WSAGetLastError())))
	{
		this->_lastError = GSocketTcpServer::ERROR_SEND;
		throw GException("GSocketTcpServer", "Error WSASend() !");
	}
	return (SendBytes);
#else
	int	l = 0;
	char	*tmp = s.ToChar();
	l = send(this->_socket, tmp, s.Size(), 0);
	delete[] tmp;
	if (l < 0)
	{
		this->_lastError = GSocketTcpServer::ERROR_SEND;
		throw GException("GSocketTcpServer", "Error send() !");
	}
	return (l);
#endif
}

int			GSocketTcpServer::Send(GSocket Socket, const GString &s)
{
#if defined (GWIN)
	int		rc, err;
	WSABUF	DataBuf;
	DWORD	SendBytes = 0;
	DataBuf.len = s.Size();
	DataBuf.buf = s.ToChar();
	rc = WSASend(Socket, &DataBuf, 1, &SendBytes, 0, NULL, NULL);
	delete[] DataBuf.buf;
	if ((rc == SOCKET_ERROR) && (WSA_IO_PENDING != (err = WSAGetLastError())))
		throw GException("GSocketTcpServer", "Error WSASend() !");
	return (SendBytes);
#else
	int	l = 0;
	char	*tmp = s.ToChar();
	l = send(Socket, tmp, s.Size(), 0);
	delete[] tmp;
	if (l < 0)
		throw GException("GSocketTcpServer", "Error send() !");
	return (l);
#endif
}

int			GSocketTcpServer::Send(GSocket Socket, void *Data, unsigned int Size)
{
#if defined (GWIN)
	int		rc, err;
	WSABUF	DataBuf;
	DWORD	SendBytes = 0;
	DataBuf.len = Size;
	DataBuf.buf = (char *)Data;
	rc = WSASend(Socket, &DataBuf, 1, &SendBytes, 0, NULL, NULL);
	if ((rc == SOCKET_ERROR) && (WSA_IO_PENDING != (err = WSAGetLastError())))
		throw GException("GSocketTcpServer", "Error WSASend() !");
	return (SendBytes);
#else
	int	l = 0;
	l = send(Socket, Data, Size, 0);
	if (l < 0)
		throw GException("GSocketTcpServer", "Error send() !");
	return (l);
#endif
}

GString	GSocketTcpServer::Receive(void)
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
	ret = WSARecv(this->_socket, &wbuf, 1, &dwBytesRet, &dwFlags, NULL, NULL);
	if (ret == SOCKET_ERROR)
		return (GString());
	return (GString::GetBuffer(wbuf.buf, dwBytesRet));
#else
	char		buffer[1024];
	int	li = 0;
	li = recv(this->_socket, buffer, sizeof(buffer), 0);
	if (li <= 0)
		return (GString(""));
	return (GString::GetBuffer(buffer, li));
#endif
}

GString	GSocketTcpServer::Receive(GSocket Socket)
{
#if defined (GWIN)
	int		ret;
	//int		len = sizeof(this->_sockaddr);
	DWORD	dwBytesRet, dwFlags;
	char	buffer[1024];
	WSABUF	wbuf;
	wbuf.len = 1024;
	wbuf.buf = buffer;
	dwFlags = 0;
	ret = WSARecv(Socket, &wbuf, 1, &dwBytesRet, &dwFlags, NULL, NULL);
	if (ret == SOCKET_ERROR)
		return (GString());
	return (GString::GetBuffer(wbuf.buf, dwBytesRet));
#else
	char		buffer[1024];
	int	li = 0;
	li = recv(Socket, buffer, sizeof(buffer), 0);
	if (li <= 0)
		return (GString(""));
	return (GString::GetBuffer(buffer, li));
#endif
}

void	GSocketTcpServer::Receive(GSocket Socket, void *Data, unsigned int Size)
{
#if defined (GWIN)
	int		ret;
	DWORD	dwBytesRet, dwFlags;
	WSABUF	wbuf;
	wbuf.len = Size;
	wbuf.buf = (char *)Data;
	dwFlags = 0;
	ret = WSARecv(Socket, &wbuf, 1, &dwBytesRet, &dwFlags, NULL, NULL);
#else
	int	li = 0;
	li = recv(Socket, Data, Size, 0);
	if (li <= 0)
		throw GException("GSocketTcpServer", "Error recv !");
#endif
}


GSocket	GSocketTcpServer::GetSocket(void) const
{
	return (this->_socket);
}

GString	GSocketTcpServer::GetLastIp(void) const
{
	return (this->_lastIp);
}

/*GString	GSocketTcpServer::GetIp(const GSocket &Sock) const
{
	if (this->_map.ExistKey(Sock))
		return (this->_map[Sock]);
	return ("");
}*/

void	GSocketTcpServer::ClearDisconnectedSocket(void)
{
	for (unsigned int i = 0; i < this->_map.Size(); ++i)
	{
		if (this->_map.Key(i) == 0)
			this->_map.EraseKey(i);
	}
}
