
#ifndef __GXMLWRITER_H__
# define __GXMLWRITER_H__

#include "GExport.h"
#include "GString.h"
#include "GDeclaration.h"
#include "GMap.hpp"

class GXmlWriter
{
	public:
		GXmlWriter(void);
		~GXmlWriter(void);
		void		SetProlog(G::XmlVersion Version, G::XmlEncoding Encoding = G::UTF8);
		void		AddComment(const GString &Comment);
		void		CreateDoctype(const GString &Doctype);
		void		AddDoctype(const GString &Param);
		void		AddContainer(const GString &Container, GStringList &List);
		void		AddElement(const GString &Name, G::XmlElement Element = G::ELEMENT_PCDATA);
		void		SetXmlVersion(G::XmlVersion Version);
		void		SetEncoding(G::XmlEncoding Encoding);
		void		Write(const GString &Content);
		void		WriteData(const GString &Data = "");
		void		StartWrite(void);
		void		EndWrite(void);
		void		Next(void);
		//void		SetElementRules(void);
		
		GString		GetXml(void) const;
		int			GetLastError(void) const;

		enum Error
		{
			NONE				= 1,
			PROLOG_NOT_FOUND	= 2,
			DOCTYPE_NOT_FOUND	= 3,
			XML_NOT_VALID		= 4
		};
		
private:
		GString						_xml;
		GString						_encoding;
		GString						_version;
		GString						_doctype;
		GStringList					_element;
		GMap<GString, GStringList>	_container;
		Error						_error;
		int							_pos;
		GStringList					_current;
		GStringList					_rest;
		unsigned int				_space;
		GString						_main;
};

#endif

/*<!DOCTYPE root
[
<!ELEMENT root (contact*)>
<!ELEMENT contact (nom,prenom,email,telephone,pass)>
<!ELEMENT nom (#PCDATA)>
<!ELEMENT prenom (#PCDATA)>
<!ELEMENT email (#PCDATA)>
<!ELEMENT telephone (#PCDATA)>
<!ELEMENT pass (#PCDATA)>
]>
*/
