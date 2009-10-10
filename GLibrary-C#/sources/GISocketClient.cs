using System;

namespace G
{
    public abstract class GISocketClient : GISocket
    {
        public abstract void    Initialize();
        public abstract void    Initialize(GString Ip, Int32 Port);
        public abstract void    Connect();
        public abstract Int16   GetLastError();

		public enum Error
		{	
			NONE			= 1,
			UNKNOW_HOST		= 2,
			ERROR_CONNECT	= 3,
			ERROR_SEND		= 4,
			ERROR_RECEIVE	= 5,
			ERROR_SOCKET	= 6
		};

    }
}
