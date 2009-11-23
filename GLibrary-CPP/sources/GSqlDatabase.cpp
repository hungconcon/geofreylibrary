
#include "GSqlDatabase.h"

GSqlDatabase::GSqlDatabase(void)
{
	mysql_init(&(this->_mysql));
    mysql_options(&(this->_mysql), MYSQL_READ_DEFAULT_GROUP, "option");
	this->_result = NULL;
}

GSqlDatabase::~GSqlDatabase(void)
{
	mysql_close(&(this->_mysql));
	mysql_library_end();
}

bool	GSqlDatabase::Connect(const GString &Host, const GString &Login, const GString &Database, const GString &Pass, unsigned int Port)
{
	char *host = Host.ToChar();
	char *login = Login.ToChar();
	char *pass = Pass.ToChar();
	char *database = Database.ToChar();
	MYSQL *res = mysql_real_connect(&(this->_mysql), host, login, pass, database, Port, NULL, 0);
	delete[] database;
	delete[] host;
	delete[] login;
	delete[] pass;
	if (res)
		return (true);
	return (false);
}

bool	GSqlDatabase::SelectDatabase(const GString &DatabaseName)
{
	char *db = DatabaseName.ToChar();
	int res = mysql_select_db(&(this->_mysql), db);
	delete[] db;
	if (res)
		return (false);
	return (true);
}

bool	GSqlDatabase::Query(const GString &Query)
{
	char *query = Query.ToChar();
	int res = mysql_query(&(this->_mysql), query);
	delete[] query;
	if (res)
		return (false);
	return (true);
}
GString	GSqlDatabase::GetHostInformation(void)
{
	return (mysql_get_host_info(&(this->_mysql)));
}
unsigned long	GSqlDatabase::GetClientVersion(void)
{
	return (mysql_get_client_version());
}
unsigned int	GSqlDatabase::GetProtocolInformation(void)
{
	return (mysql_get_proto_info(&(this->_mysql)));
}
GString			GSqlDatabase::GetServeurInformation(void)
{
	return (mysql_get_server_info(&(this->_mysql)));
}
GString			GSqlDatabase::GetClientInformation(void)
{
	return (mysql_get_client_info());
}
bool			GSqlDatabase::CreateDatabase(const GString &Name)
{
	char *req = GString("CREATE DATABASE " + Name).ToChar();
	int res = mysql_query(&(this->_mysql), req);
	delete[] req;
	if (res)	
		return (false);
	return (true);
}

bool			GSqlDatabase::DropDatabase(const GString &Name)
{
	char *req = GString("DROP DATABASE IF EXISTS " + Name).ToChar();
	int res = mysql_query(&(this->_mysql), req);
	delete[] req;
	if (res)	
		return (false);
	return (true);
}
GString			GSqlDatabase::GetError(void)
{
	return (mysql_error(&(this->_mysql)));
}

GString			GSqlDatabase::EscapeString(const GString &Str)
{
	char *str = Str.ToChar();
	char *to = new char[Str.Size() * 2 + 1];
	unsigned long nb = mysql_real_escape_string(&(this->_mysql), to, str, Str.Size());
	delete[] str;
	GString res = GString::GetBuffer(to, nb);
	delete[] to;
	return (res);
}

GString			GSqlDatabase::GetLastInformation(void)
{
	return (mysql_info(&(this->_mysql)));
}
unsigned long	GSqlDatabase::InsertId(void)
{
	return ((unsigned long)mysql_insert_id(&(this->_mysql)));
}
unsigned int	GSqlDatabase::NumRows(void)
{
	if (this->_result)
		return (1);//return ((unsigned int)mysql_num_rows(&(this->_result)));
	return (0);
}
GArray			GSqlDatabase::FetchArray(void)
{
	GArray tab;
	this->_result = mysql_use_result(&(this->_mysql));
	MYSQL_ROW row = NULL;
	MYSQL_FIELD *field;
	unsigned int num = mysql_num_fields(this->_result);
	field = mysql_fetch_field(this->_result);
	unsigned int i = 0;
	unsigned int j = 0;
	while ((row = mysql_fetch_row(this->_result)))
	{
		unsigned long *length = mysql_fetch_lengths(this->_result);
		length = mysql_fetch_lengths(this->_result);
        i = 0;
		GStringMap map;
		while (i < num)
        {
			if (row[i])
			{
				GString sub = GString::GetBuffer(row[i], (int)length[i]);
				map[field[i].name] = sub;
			}
			++i;
        }
		++j;
		tab.PushBack(map);
	}
    mysql_free_result(this->_result);
	return (tab);
}