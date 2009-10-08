
#include "GXmlReader.h"
#include "GFile.h"

using namespace std;

GXmlReader::GXmlReader(const GString &t, const GStringList &b) : _title(t), _balise(b)
{
}

GXmlReader::GXmlReader(void)
{

}

GXmlReader::~GXmlReader(void)
{
}

GStringList	GXmlReader::my_regexp(GString source, const GString &reg1, const GString &reg2)
{
	GVector<GString>		tab;

	int					i, j = 0, y = 0;
	for (i = 0; i < (int)source.Size() - 1; i++)
	{
		if ((i = source.Find(reg1, i)) < 0)
			break;
		if ((j = source.Find(reg2, i + 1)) < 0)
			break;
		y++;
	}
	if (y == 0)
		throw GException("Erreur Impossible de comprendre le dialecte : " + reg1 + " in : " + source);
	for (i = 0; i < (int)source.Size() - 1; i++)
	{
		if ((i = source.Find(reg1, i)) < 0)
			break;
		if ((j = source.Find(reg2, i + 1)) < 0)
			break;
		if (j > (int)(i + reg1.Size()))
			tab.PushBack(source.Substr(i + reg1.Size(), j).Trim());
	}
	return (tab);
}

const GVector<GString>	GXmlReader::my_regexp(const GString &source, const GString &reg)
{
	return (my_regexp(source, "<" + reg + ">", "</" + reg + ">"));
}

GVector<GStringMap>	GXmlReader::Load(const GString &file)
{
	GFile	File(file);
	File.Open(true);
	if (!File.IsOpen())
		throw GException("GXmlReader", "File not found");
	GString	Content(File.Read());
	Syntax(Content);
	return (Parser(Content));
}

GVector<GStringMap>	GXmlReader::Parser(const GString &s_content)
{
	unsigned int						i, j,k;
	GMap<GString, GString>				elem;
	GStringList							part;
	GVector<GMap<GString, GString> >	content;

	GVector<GString>	root;
	root = my_regexp(s_content, _title);
	for (i = 0; i < root.Size(); i++)
	{
		for (j = 0; j < _balise.Size(); j++)
		{
			part = my_regexp(root[i], _balise[j]);
			for (k = 0; k < part.Size(); k++)
				elem[_balise[j]] = part[k];
		}
		content.PushBack(elem);
		elem.Clear();
	}
	return (content);
}

bool	GXmlReader::Syntax(GString str)
{
	if (str.StartWith("<?xml") == false)
		throw GException("GXmlReader", "It's not an XML File");
	unsigned int	i, j, k, l, e, f;
	GStringList	temp;
	GStringList	doctype;
	GStringList	element;
	GStringList	content;
	GStringList	list;
	GStringList	elem;
	GStringList	finded;
	doctype = my_regexp(str, "<!DOCTYPE ", "]>");
	_root = doctype[0].Substr(0, doctype[0].FirstIndexOf("\n")).Trim();
	element = my_regexp(doctype[0], "<!ELEMENT ", ">");
	for (e = 0; e < element.Size(); e++)
	{
		if (e == 0 || e == 1)
		{
			temp = my_regexp(element[e], "(", ")");
			temp = temp[0].Explode(',');
			for (f = 0; f < temp.Size(); f++)
				if (temp[f][temp[f].Size() - 1] == '*')
					temp[f] = temp[f].Substr(0, temp[f].Size() - 1);
		}
		if (e == 0)
		{
			if (element[e].Find(_root) == GString::NotFound)
				throw GException("Syntax Error", "Root : '" + _root + "' in " + element[e]);
			_title = temp[0];
		}
		else if (e == 1)
		{
			if (element[e].Find(_title) == GString::NotFound)
				throw GException("Syntax Error", "Title : " + _title);
			_balise = temp;
			if (_balise.Size() != element.Size() - 2)
				throw GException("Syntax Error - Missing ELEMENT");
		}
		else
			if (element[e].Substr(0, element[e].Find(" ")) != _balise[e - 2])
				throw GException("Syntax Error");
	}
	content = my_regexp(str, _root);
	for (i = 0; i < content.Size(); i++)
	{
		list = my_regexp(content[i], _title);
		for (l = 0; l < list.Size(); l++)
		{
			elem = my_regexp(list[l], "<", ">");
			k = 0;
			for (j = 0; j < elem.Size(); j += 2)
			{
				if (_balise[k] != elem[j])
					throw GException("Syntax Error");
				k++;
			}
		}
	}
	return (true);
}
