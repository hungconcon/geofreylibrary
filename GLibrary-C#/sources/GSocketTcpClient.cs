using System;
using System.Net.Sockets;

namespace G
{
    class GSocketTcpClient //: GISocketClient
    {
        Boolean		_init;
		GString		_ip;
		Int32       _port;
		Socket		_socket;

        public          GSocketTcpClient()
        {
            this._init = false;
        }
        public          GSocketTcpClient(GString Ip, Int32 Port)
        {
	        this._ip = Ip;
	        this._port = Port;
            this._init = false;
        }
        public void     Initialize(GString Ip, Int32 Port)
        {
	        this._ip = Ip;
	        this._port = Port;
	        this.Initialize();
        }
        public void     Initialize()
        {
            this._socket = new Socket(AdressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
	        this._init = true;
        }
        ~GSocketTcpClient()
        {
	        if (this._init)
	        {
	            this._socket.Close();
            }
        }
        public void	    Connect()
        {
            if (this._init)
	        {
                this._socket.Connect(new IpEndPoint (Dns.Resolve(this._ip.ToString()).AddressList[0], this._port));
            }
        }
        public Int32    Send(GString s)
        {
            if (this._init)
            {
                Byte [] Message = System.Text.Encoding.ASCII.GetBytes(s.ToString());
                return (this._socket.Send (Message, 0, Message.Length, SocketFlags.None));
            }
            return (0);
        }
        public GString  Receive()
        {
            Byte[] message;
            this._socket.Receive(mesage);
            return (new GString(message.ToString()));
        }
    }
}