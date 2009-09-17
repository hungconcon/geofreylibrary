
#ifndef __GSQLDATABASE_H__
# define __GSQLDATABASE_H__

#include "GSocketTcpClient.h"
#include "GString.h"
#include "GString.h"

class GSqlDatabase
{
	public:
		GSqlDatabase();
		~GSqlDatabase(void);

		void	Connect(const GString &, const GString &, const GString &);
		void	SelectDatabase(const GString &);

	private:
		GSocketTcpClient	*_socket;
};

#endif
