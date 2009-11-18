
#ifndef __GSQLDATABASE_H__
# define __GSQLDATABASE_H__

#include "GExport.h"
#include "GSocketTcpClient.h"
#include "GString.h"
#include "GVector.hpp"
#include "MYSQL/mysql.h"

#if defined (GWIN)
#pragma comment(lib, "libmysql.lib")
#endif



class GEXPORTED GSqlDatabase
{
	public:
		GSqlDatabase(void);
		~GSqlDatabase(void);

		GStringList		FetchArray(void);

		GString			GetClientInformation(void);
		GString			GetServeurInformation(void);
		GString			GetHostInformation(void);
		GString			GetError(void);
		GString			EscapeString(const GString &Str);
		GString			GetLastInformation(void);

		unsigned long	GetClientVersion(void);
		unsigned int	GetProtocolInformation(void);
		unsigned int	NumRows(void);
		unsigned long	InsertId(void);

		bool			CreateDatabase(const GString &Name);
		bool			Query(const GString &Query);
		bool			Connect(const GString &Host, const GString &Login, const GString &Database, const GString &Pass = "", unsigned int Port = 3306);
		bool			SelectDatabase(const GString &DatabaseName);
		bool			DropDatabase(const GString &Database);

		

	private:
		MYSQL		_mysql;
		MYSQL_RES	*_result;
		MYSQL_ROW	*_row;

};

#endif
