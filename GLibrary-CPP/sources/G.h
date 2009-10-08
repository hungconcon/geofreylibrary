
#ifndef __GDEC_H__
# define __GDEC_H__

namespace G
{
		enum LanguageOption
		{
			FRENCH,
			ENGLISH,
			SPANISH,
			ITALIAN,
		};

		enum CaseOption
		{
			CASE_SENSITIVE,
			CASE_INSENSITIVE
		};

		enum XmlVersion
		{
			XML_1_0,
			XML_1_1
		};

		enum XmlElement
		{
			ELEMENT_ANY,
			ELEMENT_EMPTY,
			ELEMENT_PCDATA
		};

		enum XmlEncoding
		{
			UTF8,
			ISO
		};


		enum SocketOption
		{

		};

		enum SplitOption
		{
			SKIP_EMPTY_PARTS	= 0x001,
			KEEP_EMPTY_PARTS	= 0x002
		};
		enum TrimOption
		{
			TRIM_BLANK			= 0x001,
			TRIM_SPACE			= 0x002,
			TRIM_TAB			= 0x003,
			TRIM_ENTER			= 0x004,
			TRIM_NUMBER			= 0x005,
			TRIM_ALPHA			= 0x006,
			TRIM_ALPHANUM		= 0x007
		};

		enum IndexOption
		{
			INDEX_ALL_CHAR		= 0x001,
			INDEX_THIS_CHAR		= 0x002
		};

		enum OrderOption
		{
			ORDER_ASC,
			ORDER_DESC
		};

		enum SqlOption
		{
			MYSQL
		};

		enum Exception
		{
			CANNOT_TRADUCT_THIS_LANGUAGE,
			CANNOT_CREATE_DIRECTORY,
			CANNOT_GET_CURRENT_PATH,
			CANNOT_REMOVE_DIRECTORY,

			CANNOT_FIND_DOCTYPE,

			DIRECTORY_NOT_EXIST,
	
			OUT_OF_RANGE,

			VECTOR_IS_EMPTY,

			SOCKET_INIT_ERROR,
			SOCKET_CONNECT_ERROR,
			SOCKET_SEND_ERROR,
			SOCKET_UNKNOW_HOST,

			BAD_REGEXP_FORMAT,

			NOT_A_BOOLEEN,
			NOT_AN_INTEGER
		};

};

#endif
