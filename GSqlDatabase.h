
#ifndef __GSQLDATABASE_H__
# define __GSQLDATABASE_H__

#include "GSocketTcpClient.h"
#include "GString.h"
#include "GString.h"

class GSqlDatabase
{
	public:
		GSqlDatabase(void);
		~GSqlDatabase(void);

		void	Connect(const GString &Host, const GString &Login, const GString &Pass);
		void	SelectDatabase(const GString &);

	private:
		GSocketTcpClient	_socket;
};

#endif
