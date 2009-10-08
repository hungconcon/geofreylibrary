
#include "GInternet.h"

bool	GInternet::IsConnected(void)
{
	DWORD dwConnectionStatus;
	if (InternetGetConnectedState(&dwConnectionStatus, NULL) == TRUE)
		return (true);
	return (false);
}

