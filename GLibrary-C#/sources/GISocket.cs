using System;
using System.Net;
using System.Net.Sockets;

namespace G
{
    public abstract class GISocket
    {

        public abstract Int32       Send(GString Message);
		public abstract GString     Receive();
        public abstract Socket      GetSocket();

        public static Int32        Send(GISocket Socket, GString ToSend)
        {
	        return (Socket.Send(ToSend));
        }

        public static GString      Receive(GISocket Socket)
        {
	        return (Socket.Receive());
        }
    }
}

