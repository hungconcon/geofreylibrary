
#include "GSmtp.h"

GSmtp::GSmtp(const GString &ip, unsigned int port)
{
	this->_serveur = ip;
	this->_port = port;
	this->MakeMap();
}

GSmtp::GSmtp(void)
{
	this->MakeMap();
}

GSmtp::~GSmtp(void)
{

}

void	GSmtp::MakeMap(void)
{
	this->_map["211"] = "";
	this->_map["214"] = "";
	this->_map["220"] = "";
	this->_map["221"] = "";
	this->_map["250"] = "";
	this->_map["251"] = "";
	this->_map["354"] = "";
	this->_map["421"] = "";
	this->_map["450"] = "";
	this->_map["451"] = "";
	this->_map["452"] = "";
	this->_map["500"] = "";
	this->_map["501"] = "";
	this->_map["502"] = "";
	this->_map["503"] = "";
	this->_map["504"] = "";
	this->_map["550"] = "";
	this->_map["551"] = "";
	this->_map["552"] = "";
	this->_map["553"] = "";
	this->_map["554"] = "";
}

void	GSmtp::SetServer(const GString &SMTP, unsigned int Port)
{
	this->_serveur = SMTP;
	this->_port = Port;
}

void	GSmtp::AddRecipient(const GString &Mail)
{
	GString str = "<" + Mail + ">";
	this->_listSend.PushBack(str);
}

void	GSmtp::AddRecipient(const GString &Mail, const GString &Name)
{
	GString str = "\"" + Name + "\" <" + Mail + ">";
	this->_listSend.PushBack(str);
}


void	GSmtp::DeleteRecipient(const GString &Mail)
{
	this->_listSend.Delete(Mail);
}

void	GSmtp::SetSubject(const GString &Subject)
{
	this->_subject = Subject;
}

void	GSmtp::SetSender(const GString &Mail)
{
	this->_from = Mail;
}

void	GSmtp::SetSender(const GString &Mail, const GString &Name)
{
	this->_from = Mail;
	this->_fromName = Name;
}

void	GSmtp::CheckError(const GString &Error)
{

}

void	GSmtp::Send(void)
{
	this->_socket.Init(this->_serveur, this->_port);
	this->_socket.Connect();
	GString recept = this->_socket.Receive();
	this->_packets += recept;
	std::cout << recept << std::endl;
	GString Hello = "HELO " + this->_serveur + "\r\n";
	this->_packets += Hello;
	this->_socket.Send(Hello);
	recept = this->_socket.Receive();
	std::cout << recept << std::endl;
	this->_packets += recept;
	if (!recept.StartWith("250 "))
	{
		CheckError(recept.Substr(0, 3));
		return ;
	}
	GString MailFrom = "MAIL FROM: ";
	if (!this->_fromName.IsEmpty())
		MailFrom += "\"" + this->_fromName + "\" ";
	MailFrom += "<" + this->_from + ">\r\n";
	this->_socket.Send(MailFrom);
	recept = this->_socket.Receive();
	std::cout << recept << std::endl;
	if (!recept.StartWith("250 "))
	{
		CheckError(recept.Substr(0, 3));
		return ;
	}
	GString RcptTo = "RCPT TO: ";
	unsigned int i = 0;
	while (i < this->_listSend.Size())
	{
		if (i != 0)
			RcptTo += ", ";
		RcptTo += this->_listSend[i];
	}
	RcptTo += "\r\n";
	this->_socket.Send(RcptTo);
	recept = this->_socket.Receive();
	std::cout << recept << std::endl;
}

GString		GSmtp::GetPackets(void)
{
	return (this->_packets);
}
