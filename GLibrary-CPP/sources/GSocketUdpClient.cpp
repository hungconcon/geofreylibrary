
#include "GSocketUdpClient.h"

GSocketUdpClient::GSocketUdpClient(void) : _init(false)
{
}

GSocketUdpClient::GSocketUdpClient(const GString &ip, unsigned int port) : _init(false)
{
	this->_ip = ip;
	this->_port = port;
}

GSocketUdpClient::~GSocketUdpClient(void)
{
	if (this->_init)
	{
	#if defined (GWIN)
		closesocket(this->_socket);
		WSACleanup();
	#else
		close(this->_socket);
	#endif
	}
}

void		GSocketUdpClient::Init(const GString &Ip, unsigned int Port)
{
	this->_ip = Ip;
	this->_port = Port;
	this->Init();
}

void		GSocketUdpClient::Init(void)
{
#if defined (GWIN)
	WSADATA	wsaData;
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != NO_ERROR)
	{
		this->_lastError = GSocketUdpClient::ERROR_SOCKET;
		throw GException("GSocketUdpClient", "Error WSAStartup() !");
	}
	this->_socket = WSASocket(AF_INET, SOCK_DGRAM, 0, 0, 0, 0);
	if (this->_socket == INVALID_SOCKET)
	{
		this->_lastError = GSocketUdpClient::ERROR_SOCKET;
		throw GException("GSocketUdpClient", "Error WSASocket()");
	}
	this->_sockaddr.sin_family = AF_INET;
	char	*tmp = this->_ip.ToChar();
	this->_sockaddr.sin_addr.S_un.S_addr = inet_addr(tmp);
	delete[] tmp;
	if (WSAHtons(this->_socket, this->_port, &this->_sockaddr.sin_port) == SOCKET_ERROR)
	{
		this->_lastError = GSocketUdpClient::ERROR_SOCKET;
		throw GException("GSocketUdpClient", "Error WSAHtons()");
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
			this->_lastError = GSocketUdpClient::UNKNOW_HOST;
			throw GException("GSocketUdpClient", "Unknow Host gethostbyname() return NULL !");
		}
	}
	delete[] tmp;
	if ((int)(this->_socket = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
	{
		this->_lastError = GSocketUdpClient::ERROR_SOCKET;
		throw GException("GSocketUdpClient", "Error socket()");
	}
	this->_sockaddr.sin_family = AF_INET;
	this->_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	this->_sockaddr.sin_port = htons(this->_port);
#endif
	this->_init = true;
}

int			GSocketUdpClient::GetLastError(void) const
{
	return (this->_lastError);
}

void		GSocketUdpClient::Connect(void)
{
	if (this->_init)
	{
	#if defined (GWIN)
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
				this->_lastError = GSocketUdpClient::UNKNOW_HOST;
				throw GException("GSocketUdpClient", "Unknow Host gethostbyname() return NULL !");
			}
		}
		delete[] tmp;
		this->_sockaddr.sin_family = AF_INET;
		this->_sockaddr.sin_addr = *((in_addr *)he->h_addr);
		if (WSAHtons(this->_socket, this->_port, &this->_sockaddr.sin_port) == SOCKET_ERROR)
		{
			this->_lastError = GSocketUdpClient::ERROR_SOCKET;
			throw GException("GSocketUdpClient", "Error in WSAHtons()");
		}
		if (WSAConnect(this->_socket, (SOCKADDR*)&this->_sockaddr, sizeof(this->_sockaddr), NULL, NULL, NULL, NULL) == SOCKET_ERROR)
		{
			closesocket(this->_socket);
			WSACleanup();
			this->_lastError = GSocketUdpClient::ERROR_CONNECT;
			throw GException("GSocketUdpClient", "Error WSAConnect(), unable to connect to IpAdresse !");
		}
	#else
		hostent *he;
		char	*tmp = this->_ip.ToChar();
		if ((he = gethostbyname(tmp) == NULL)
		{
			delete[] tmp;
			this->_lastError = GSocketUdpClient::UNKNOW_HOST;
			throw GException("GSocketUdpClient", "Unknow Host gethostbyname() return NULL !");
		}
		delete[] tmp;
		this->_sockaddr.sin_family = AF_INET;
		this->_sockaddr.sin_addr = *((in_addr *)he->h_addr);
		this->_sockaddr.sin_port = htons(_port);
		if (connect(this->_socket, (struct sockaddr *)&this->_sockaddr, sizeof(this->_sockaddr)) < 0)
		{
			close(this->_socket);
			this->_lastError = GSocketUdpClient::ERROR_CONNECT;
			throw GException("GSocketUdpClient", "Error connect(), unable to connect to IpAdresse !");
		}
	#endif
	}
}



int			GSocketUdpClient::Send(const GString &s)
{
	if (this->_init)
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
			this->_lastError = GSocketUdpClient::ERROR_SEND;
			throw GException("GSocketUdpClient", "Error WSASend() !");
		}
		return (SendBytes);
	#else
		int	l = 0;
		char	*tmp = s.ToChar();
		l = sendto(this->_socket, tmp, s.Size(), 0, 0, 0);
		delete[] tmp;
		if (l < 0)
		{
			this->_lastError = GSocketUdpClient::ERROR_SEND;
			throw GException("GSocketUdpClient", "Error send() !");
		}
		return (l);
	#endif
	}
	return (0);
}

int			GSocketUdpClient::Send(void *s, unsigned int size)
{
	if (this->_init)
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
			this->_lastError = GSocketUdpClient::ERROR_SEND;
			throw GException("GSocketUdpClient", "Error WSASend() !");
		}
		return (SendBytes);
	#else
		int	l = 0;
		l = sendto(this->_socket, s, size, 0, 0, 0);
		if (l < 0)
		{
			this->_lastError = GSocketUdpClient::ERROR_SEND;
			throw GException("GSocketUdpClient", "Error send() !");
		}
		return (l);
	#endif
	}
	return (0);
}

GString		GSocketUdpClient::Receive(void)
{
	if (this->_init)
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
	return ("");
}

void		GSocketUdpClient::Receive(void *s, unsigned int size)
{
	if (this->_init)
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
		throw GException("GSocketUdpClient", "Error WSARecvFrom");
	#else
		int	li = 0;
		li = recvfrom(this->_socket, s, size, 0, 0, 0);
		if (li <= 0)
			throw GException("GSocketUdpClient", "Error recvfrom");
	#endif
	}
}

GSocket		GSocketUdpClient::GetSocket(void) const
{
	if (this->_init)
		return (this->_socket);
	return (0);
}

