
#ifndef __GXMLREADER_H__
# define __GXMLREADER_H__

#include "GString.h"
#include "GVector.hpp"
#include "GMap.hpp"
#include "GVector.hpp"
#include <fstream>

class GXmlReader
{
	public:
		GXmlReader(void);
		GXmlReader(const GString &, const GStringList &);
		~GXmlReader(void);
		
		GVector<GStringMap>	Load(const GString &);
		GVector<GStringMap>	Parser(const GString &);

	private:
		GString		_title;
		GString		_root;
		GStringList	_balise;
		bool		Syntax(GString);
		GStringList	my_regexp(GString source, const GString &reg1, const GString &reg2);
		const GStringList	my_regexp(const GString &, const GString &);
};

#endif
