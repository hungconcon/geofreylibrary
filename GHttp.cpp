
#include "GHttp.h"

GHttp::GHttp(const GString &host, unsigned int port)
{
	this->_proxyHost = "";
	this->_proxyPort = 0;
	this->_proxyUser = "";
	this->_proxyPass = "";
	this->_host = host;
	this->_port = port;
	this->_socket.Init();
	this->_socket.Connect();
}

GHttp::~GHttp(void)
{
}

void	GHttp::SetUser(const GString &user, const GString &pass)
{
	this->_user = user;
	this->_pass = pass;
}

void	GHttp::SetProxy(const GString &host, unsigned int port, const GString &user, const GString &pass)
{
	this->_proxyHost = host;
	this->_proxyPort = port;
	this->_proxyUser = user;
	this->_proxyPass = pass;
}

void	GHttp::SetProxy(const GString &host, unsigned int port)
{
	this->_proxyHost = host;
	this->_proxyPort = port;
}

void	GHttp::Post(const GString &p, const GString &tab)
{
	GString page(p);
	GString	message(tab);
	if (!page.StartWith("http://"))
	{
		page = this->_host + page;
		if (!page.StartWith("http://"))
			page = "http://" + page;
	}
	GString chaine;
	chaine  = "POST " + page + " HTTP/1.1\r\n";
	chaine += "Host: " + this->_host + "\r\n";
	if (!this->_proxyUser.IsEmpty())
	{
		chaine += "Proxy-Authorization: Basic " + GCryptography::GBase64::Encode(this->_proxyUser + ":" + this->_proxyPass) + "\r\n";
		chaine += "Proxy-Connection : keep-alive\r\n";
	}
	if (!this->_user.IsEmpty())
		chaine += "Authorization: Basic " + GCryptography::GBase64::Encode(this->_user + ":" + this->_pass) + "\r\n";
	chaine += "Content-Type: application/x-www-form-urlencoded\r\n";
	chaine += "Content-Length: " + GString(message.Size()) + "\r\n";
	chaine += "\r\n";
	chaine += message + "\r\n";
	chaine += "\r\n";
	this->_socket.Send(chaine);
}

GString		GHttp::Get(const GString &g)
{
	GString	page(g);
	if (!page.StartWith("http://"))
	{
		page = this->_host + page;
		if (!page.StartWith("http://"))
			page = "http://" + page;
	}
	GString	str = "GET " + page + " HTTP/1.1\r\n";
	str += "Host: " + this->_host + "\r\n";
	if (!this->_proxyUser.IsEmpty())
	{
		str += "Proxy-Authorization: Basic " + GCryptography::GBase64::Encode(this->_proxyUser + ":" + this->_proxyPass) + "\r\n";
		str += "Proxy-Connection : keep-alive\r\n";
	}
	else
	{
		str += "Keep-Alive: 20000\r\n";
		str += "Connection : keep-alive\r\n";
	}
	if (!this->_user.IsEmpty())
		str += "Authorization: Basic " + GCryptography::GBase64::Encode(this->_user + ":" + this->_pass) + "\r\n";
	str += "\r\n";
	this->_socket.Send(str);
	GString rectot;
	while (true)
	{
		GString rec;
		rec = this->_socket.Receive();
		if (rec.Size() < 1024)
		{
			rectot += rec;
			GString	sub = rec.Substr(0, rec.Find("\r\n"));
			GStringList	tab = sub.Split(" ");
			if (tab.Size() > 2)
			{
				//GESTION DES ERREUR
			}
			int	pos = rec.Find("\r\n\r\n");
			if (pos != GString::NotFound)
				;//this->_response = this->_response.Substr(pos + 4);
		}
	}
	return (rectot);
}

