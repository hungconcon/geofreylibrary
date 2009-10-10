using System;
using System.Net.Sockets;
using System.Net;

namespace G
{
    public class GSocketTcpClient : GISocketClient
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
        public override Socket GetSocket()
        {
            return (this._socket);
        }
        public override void     Initialize(GString Ip, Int32 Port)
        {
	        this._ip = Ip;
	        this._port = Port;
	        this.Initialize();
        }
        public override void     Initialize()
        {
            this._socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
	        this._init = true;
        }
        ~GSocketTcpClient()
        {
	        if (this._init)
	        {
	            this._socket.Close();
            }
        }
        public override void	    Connect()
        {
            if (this._init)
	        {
                this._socket.Connect(new IPEndPoint (Dns.Resolve(this._ip.ToString()).AddressList[0], this._port));
            }
        }
        public override Int16 GetLastError()
        {
            return (1);
        }

        public override Int32    Send(GString s)
        {
            if (this._init)
            {
                Byte [] Message = System.Text.Encoding.ASCII.GetBytes(s.ToString());
                return (this._socket.Send (Message, 0, Message.Length, SocketFlags.None));
            }
            return (0);
        }
        public override GString  Receive()
        {
            Byte[] message = new Byte[1024];
            this._socket.Receive(message);
            return (new GString(message.ToString()));
        }
    }
}