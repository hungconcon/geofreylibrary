
#ifndef		__GISOCKET_H__
# define	__GISOCKET_H__

#include "GString.h"
#include "GExport.h"

#if defined (GWIN)
#		include "windows.h"
#		include "Winsock2.h"
typedef int				socklen_t;
typedef SOCKET			GSocket;
#pragma comment(lib, "ws2_32.lib")
#else
#		include <sys/types.h>
#		include <sys/socket.h>
#		include <netdb.h>
#		include <netinet/in.h>
#		include <arpa/inet.h>
#		define INVALID_SOCKET	-1
#		define SOCKET_ERROR		-1
typedef	unsigned int	GSocket;
#endif

class	GEXPORTED GISocket
{
	public:
		virtual ~GISocket(void){};
		
		virtual int					Send(const GString &) = 0;
		virtual int					Send(void *Data, unsigned int Size) = 0;
		static	int					Send(GISocket *Socket, const GString &ToSend);
		static	int					Send(GISocket *Socket, void *Data, unsigned int Size);

		virtual GString				Receive(void) = 0;
		virtual void				Receive(void *Data, unsigned int Size) = 0;
		static	GString				Receive(GISocket *Socket);
		static	void				Receive(GISocket *Socket, void *Data, unsigned int Size);

		virtual GSocket				GetSocket(void) const = 0;
		virtual void				Close(void) = 0;
		static void					Close(GISocket *Socket);

};

#endif
