
#include "GSocketTcpClient.h"

GSocketTcpClient::GSocketTcpClient(void)
{
}

GSocketTcpClient::GSocketTcpClient(const GString &ip, unsigned int port)
{
	this->_ip = ip;
	this->_port = port;
}

void	GSocketTcpClient::Init(const GString &Ip, unsigned int Port)
{
	this->_ip = Ip;
	this->_port = Port;
	this->Init();
}

void	GSocketTcpClient::Init(void)
{
#if defined (GWIN)
	WSADATA	wsaData;
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != NO_ERROR)
	{
		throw GException("GSocketTcpClient", "Error WSAStartup() !");
		this->_lastError = GSocketTcpClient::ERROR_SOCKET;
	}
	this->_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
	if (this->_socket == INVALID_SOCKET)
	{
		throw GException("GSocketTcpClient", "Error WSASocket()");
		this->_lastError = GSocketTcpClient::ERROR_SOCKET;
	}
	hostent *he;
	char	*tmp = this->_ip.ToChar();
	if ((he = gethostbyname(tmp)) == NULL)
	{
		this->_ip = this->_ip.Replace("http://", "");
		delete[] tmp;
		tmp = this->_ip.ToChar();
		if ((he = gethostbyname(tmp)) == NULL)
		{
			delete[] tmp;
			this->_lastError = GSocketTcpClient::UNKNOW_HOST;
			throw GException("GSocketTcpClient", "Unknow Host gethostbyname() return NULL !");
		}
	}
	delete[] tmp;
	this->_sockaddr.sin_family = AF_INET;
	this->_sockaddr.sin_addr = *((in_addr *)he->h_addr);
	if (WSAHtons(this->_socket, this->_port, &this->_sockaddr.sin_port) == SOCKET_ERROR)
	{
		this->_lastError = GSocketTcpClient::ERROR_SOCKET;
		throw GException("GSocketTcpClient", "Error WSAHtons()");
	}
#else
	protoent *prot;
	char	*tmp = this->_ip.ToChar();
	if ((prot = getprotobyname(tmp)) == 0)
	{
		delete[] tmp;
		this->_ip = this->_ip.Replace("http://", "");
		tmp = this->_ip.ToChar();
		if ((prot = getprotobyname(tmp)) == 0)
		{
			delete[] tmp;
			this->_lastError = GSocketTcpClient::UNKNOW_HOST;
			throw GException("GSocketTcpClient", "Unknow Host gethostbyname() return NULL !");
		}
	}
	delete[] tmp;
	if ((int)(this->_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		this->_lastError = GSocketTcpClient::ERROR_SOCKET;
		throw GException("GSocketTcpClient", "Error socket()");
	}
	this->_sockaddr.sin_family = AF_INET;
	this->_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	this->_sockaddr.sin_port = htons(port);
#endif
}

GSocketTcpClient::~GSocketTcpClient(void)
{
#if defined (GWIN)
	closesocket(this->_socket);
	WSACleanup();
#else
	close(this->_socket);
#endif
}

int			GSocketTcpClient::GetLastError(void) const
{
	return (this->_lastError);
}

void		GSocketTcpClient::Connect(void)
{
#if defined (GWIN)

	if (WSAConnect(this->_socket, (SOCKADDR*)&this->_sockaddr, sizeof(this->_sockaddr), NULL, NULL, NULL, NULL) == SOCKET_ERROR)
    {
		closesocket(this->_socket);
		WSACleanup();
		throw GException("GSocketTcpClient", "Error WSAConnect(), unable to connect to IpAdresse !");
		this->_lastError = GSocketTcpClient::ERROR_CONNECT;
	}
#else
	if (connect(this->_socket, (struct sockaddr *)&this->_sockaddr, sizeof(this->_sockaddr)) < 0) 
    {
		close(this->_socket);
		throw GException("GSocketTcpClient", "Error connect(), unable to connect to IpAdresse !");
		this->_lastError = GSocketTcpClient::ERROR_CONNECT;
    }
#endif
}



int			GSocketTcpClient::Send(const GString &s)
{
#if defined (GWIN)
	int		rc, err;
	WSABUF	DataBuf;
	DWORD	SendBytes = 0;
	DataBuf.len = s.Size();
	DataBuf.buf = s.ToChar();
	rc = WSASend(this->_socket, &DataBuf, 1, &SendBytes, 0, NULL, NULL);
	delete[] DataBuf.buf;
	if ((rc == SOCKET_ERROR) && (WSA_IO_PENDING != (err = WSAGetLastError())))
	{
		this->_lastError = GSocketTcpClient::ERROR_SEND;
		throw GException("GSocketTcpClient", "Error WSASend() !");
	}
	return (SendBytes);
#else
	int	l = 0;
	char	*tmp = s.ToChar();
	l = send(this->_socket, tmp, s.Size(), 0);
	delete[] tmp;
	if (l < 0)
	{
		this->_lastError = GSocketTcpClient::ERROR_SEND;
		throw GException("GSocketTcpClient", "Error send() !");
	}
	return (l);
#endif
}

int			GSocketTcpClient::Send(void *s, unsigned int size)
{
#if defined (GWIN)
	int		rc, err;
	WSABUF	DataBuf;
	DWORD	SendBytes = 0;
	DataBuf.len = size;
	DataBuf.buf = (char *)s;
	rc = WSASend(this->_socket, &DataBuf, 1, &SendBytes, 0, NULL, NULL);
	if ((rc == SOCKET_ERROR) && (WSA_IO_PENDING != (err = WSAGetLastError())))
	{
		this->_lastError = GSocketTcpClient::ERROR_SEND;
		throw GException("GSocketTcpClient", "Error WSASend() !");
	}
	return (SendBytes);
#else
	int	l = 0;
	l = send(this->_socket, s, size, 0);
	if (l < 0)
	{
		this->_lastError = GSocketTcpClient::ERROR_SEND;
		throw GException("GSocketTcpClient", "Error send() !");
	}
	return (l);
#endif
}

GString	GSocketTcpClient::Receive(void)
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

void	GSocketTcpClient::Receive(void *s, unsigned int size)
{
#if defined (GWIN)
	int		ret;
	int		len = sizeof(this->_sockaddr);
	DWORD	dwBytesRet, dwFlags;
	WSABUF	wbuf;
	wbuf.len = size;
	wbuf.buf = (char *)s;
	dwFlags = 0;
	ret = WSARecv(this->_socket, &wbuf, 1, &dwBytesRet, &dwFlags, NULL, NULL);
	if (ret == SOCKET_ERROR)
		throw GException("GSocketTcpClient", "Error WSARecv");
#else
	int	li = 0;
	li = recv(this->_socket, s, size, 0);
#endif
}

GSocket		GSocketTcpClient::GetSocket(void) const
{
	return (this->_socket);
}

