
#ifndef __GISQLDATABASE_H__
# define __GISQLDATABASE_H__

#include "GExport.h"
#include "GString.h"
#include "GSocketTcpClient.h"

class GEXPORTED GISqlDatabase
{
	public:
		virtual unsigned long	GetClientVersion(void) = 0;
		virtual unsigned int	GetProtocolInformation(void) = 0;
		virtual unsigned int	NumRows(void) = 0;
		virtual unsigned long	InsertId(void) = 0;

		virtual bool			CreateDatabase(const GString &Name) = 0;
		virtual bool			Query(const GString &Query) = 0;
		virtual bool			Connect(const GString &Host, const GString &Login, const GString &Database, const GString &Pass, unsigned int Port) = 0;
		virtual bool			SelectDatabase(const GString &DatabaseName) = 0;
		virtual bool			DropDatabase(const GString &Database) = 0;
};


#endif