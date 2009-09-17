
#include "GXmlWriter.h"


GXmlWriter::GXmlWriter(void)
{
	this->_xml = "";
	this->_error = GXmlWriter::NONE;
	this->_encoding = "";
	this->_version = "";
	this->_doctype = "";
	this->_pos = -1;
	this->_space = 0;
	this->_main = "";
}

GXmlWriter::~GXmlWriter(void)
{

}
void	GXmlWriter::SetProlog(G::XmlVersion Version, G::XmlEncoding Encoding)
{
	if (!this->_xml.StartWith("<?xml "))
	{
		GString temp("<?xml ");
		if (Version == G::XML_1_0)
		{
			this->_version = "1.0";
			temp += "version=\"1.0\" ";
		}
		else if (Version == G::XML_1_1)
		{
			temp += "version=\"1.1\" ";
			this->_version = "1.1";
		}
		if (Encoding == G::UTF8)
		{
			this->_encoding = "UTF-8";
			temp += "encoding=\"UTF-8\" ";
		}
		else if (Encoding == G::ISO)
		{
			temp += "encoding=\"ISO-8859-1\" ";
			this->_encoding = "ISO-8859-1";
		}
		temp += "?>\n";
		this->_xml = temp + this->_xml;
	}
	int pos;
	if ((pos = this->_xml.Find("]>\n")) != GString::NotFound)
		this->_pos = pos;
}

GString	GXmlWriter::GetXml(void) const
{
	return (this->_xml);
}

void	GXmlWriter::AddComment(const GString &Comment)
{
	this->_xml += "<!-- " + Comment + " -->\n";
}

int		GXmlWriter::GetLastError(void) const
{
	return (this->_error);
}

void	GXmlWriter::CreateDoctype(const GString &Doctype)
{
	if (this->_xml.Find("<!DOCTYPE", GString::CaseInsensitive) == GString::NotFound)
	{
		int pos = this->_xml.Find("?>\n");
		this->_doctype = Doctype;
		if (pos == GString::NotFound)
			this->_xml = "<!DOCTYPE " + Doctype + "\n[\n]>\n" + this->_xml;
		else
			this->_xml = this->_xml.Insert(pos + 3, "<!DOCTYPE " + Doctype + "\n[\n]>\n");
	}
	int pos;
	if ((pos = this->_xml.Find("]>\n")) != GString::NotFound)
		this->_pos = pos;
}

void	GXmlWriter::AddElement(const GString &Name, G::XmlElement Element)
{
	GString find("<!DOCTYPE " + this->_doctype + "\n[\n");
	int pos;
	if ((pos = this->_xml.Find(find)) != GString::NotFound)
	{
		if (!this->_element.Contain(Name))
		{
			GString Type;
			if (Element == G::ELEMENT_ANY)
				Type = "ANY";
			else if (Element == G::ELEMENT_EMPTY)
				Type = "EMPTY";
			else if (Element == G::ELEMENT_PCDATA)
				Type = "#PCDATA";
			this->_element.PushBack(Name);
			this->_xml = this->_xml.Insert(pos + find.Size(), "<!ELEMENT " + Name + " (" + Type + ")>\n");
		}
	}
	else
	{
		throw GException("GXmlWriter", "Cannot find DOCTYPE !");
		this->_error = GXmlWriter::DOCTYPE_NOT_FOUND;
	}
	if ((pos = this->_xml.Find("]>\n")) != GString::NotFound)
		this->_pos = pos;
}
void	GXmlWriter::AddDoctype(const GString &Param)
{
	GString find("<!DOCTYPE " + this->_doctype + "\n[\n");
	int pos;
	if ((pos = this->_xml.Find(find)) != GString::NotFound)
	{
		this->_xml = this->_xml.Insert(pos + find.Size(), "<!ELEMENT " + this->_doctype + " (" + Param + ")*>\n");
	}
	else
	{
		throw GException("GXmlWriter", "Cannot find DOCTYPE !");
		this->_error = GXmlWriter::DOCTYPE_NOT_FOUND;
	}
	if ((pos = this->_xml.Find("]>\n")) != GString::NotFound)
		this->_pos = pos;
}

void	GXmlWriter::AddContainer(const GString &Container, GStringList &List)
{
	GString find("<!DOCTYPE " + this->_doctype + "\n[\n");
	int pos;
	if ((pos = this->_xml.Find(find)) != GString::NotFound)
	{
		if (!this->_container.ExistKey(Container))
		{
			if (this->_main.IsEmpty())
				this->_main = Container;
			this->_container[Container] = List;
			GString str("<!ELEMENT " + Container + " (");
			for (unsigned int i = 0; i < List.Size(); ++i)
			{
				if (i != 0)
					str += ", ";
				str += List[i];
			}
			str += ")>\n";
			this->_xml = this->_xml.Insert(pos + find.Size(), str);
		}
	}
	else
	{
		throw GException("GXmlWriter", "Cannot find DOCTYPE !");
		this->_error = GXmlWriter::DOCTYPE_NOT_FOUND;
	}
	if ((pos = this->_xml.Find("]>\n")) != GString::NotFound)
		this->_pos = pos;
}

void	GXmlWriter::SetXmlVersion(G::XmlVersion Version)
{
	GString find("version=\"" + this->_version + "\"");
	if (this->_xml.Find(find) != GString::NotFound)
	{
		if (Version == G::XML_1_0)
			this->_version = "1.0";
		else if (Version == G::XML_1_1)
			this->_version = "1.1";
		this->_xml = this->_xml.Replace(find, "version=\"" + this->_version + "\"");
	}
	else
	{
		throw GException("GXmlWriter", "Cannot find PROLOG !");
		this->_error = GXmlWriter::PROLOG_NOT_FOUND;
	}
	int pos;
	if ((pos = this->_xml.Find("]>\n")) != GString::NotFound)
		this->_pos = pos;
}

void	GXmlWriter::SetEncoding(G::XmlEncoding Encoding)
{
	GString find("encoding=\"" + this->_encoding + "\"");
	if (this->_xml.Find(find) != GString::NotFound)
	{
		if (Encoding == G::UTF8)
			this->_encoding = "UTF-8";
		else if (Encoding == G::ISO)
			this->_encoding = "ISO-8859-1";
		this->_xml = this->_xml.Replace(find, "encoding=\"" + this->_encoding + "\"");
	}
	else
	{
		throw GException("GXmlWriter", "Cannot find PROLOG !");
		this->_error = GXmlWriter::PROLOG_NOT_FOUND;
	}
	int pos;
	if ((pos = this->_xml.Find("]>\n")) != GString::NotFound)
		this->_pos = pos;	
}

void	GXmlWriter::StartWrite(void)
{
	this->_xml += "<" + this->_doctype + ">\n";
	this->_rest.PushBack(this->_main);
	++this->_space;
}
void	GXmlWriter::Next(void)
{
	this->WriteData();	
}

void	GXmlWriter::Write(const GString &Content)
{
	this->_xml += Content;
}

void	GXmlWriter::WriteData(const GString &Content)
{
	if (this->_rest.Size() != 0)
	{
		if (this->_container.ExistKey(this->_rest[0]))
		{
			for (unsigned int i = 0; i < this->_space; ++i)
				this->_xml += "\t";
			this->_xml += "<" + this->_rest[0] + ">\n";
			++this->_space;
			GStringList l = this->_container[this->_rest[0]];
			this->_current.PushFront(this->_rest[0]);
			this->_rest.Erase(0);
			for (int i = l.Size() - 1; i >= 0; --i)
				this->_rest.PushFront(l[i]);
			this->WriteData(Content);
		}
		else
		{
			for (unsigned int i = 0; i < this->_space; ++i)
				this->_xml += "\t";
			if (Content.IsEmpty())
				this->_xml += "</" + this->_rest[0] + ">\n";
			else
				this->_xml += "<" + this->_rest[0] + ">" + Content + "</" + this->_rest[0] + ">\n";
			this->_rest.Erase(0);
		}
	}
	else
	{
		if (this->_current.Size() >= 1)
		{
			--this->_space;
			for (unsigned int i = 0; i < this->_space; ++i)
				this->_xml += "\t";
			this->_xml += "</" + this->_current[0] + ">\n";
			this->_current.Erase(0);
			this->WriteData(Content);
		}
		else
		{
			this->_rest.PushBack(this->_main);
			this->WriteData(Content);
		}
	}
	
}

void	GXmlWriter::EndWrite(void)
{
	if (this->_rest.Size() > 0)
	{
		this->WriteData();
		this->EndWrite();
	}
	else if (this->_current.Size() >= 1)
	{
		--this->_space;
		for (unsigned int i = 0; i < this->_space; ++i)
			this->_xml += "\t";
		this->_xml += "</" + this->_current[0] + ">\n";
		this->_current.Erase(0);
		this->EndWrite();
	}
	else if (this->_current.Size() == 0)
		this->_xml += "</" + this->_doctype + ">\n";
}

