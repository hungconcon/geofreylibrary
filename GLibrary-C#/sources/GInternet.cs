using System;
using System.Runtime.InteropServices;

namespace G
{
    public class GInternet
    {
        [DllImport("wininet.dll")]
        public extern static bool InternetGetConnectedState( out int Description, int ReservedValue ) ;

        public static Boolean IsConnected()
        {
            int Desc ;
            return (InternetGetConnectedState(out Desc, 0));
        }
    }
}
