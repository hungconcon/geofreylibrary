#ifndef GREGEXP_H__
#define GREGEXP_H__

#include "GRegExpOpt.h"

class GRegExp
{
public:
	GRegExp(GString preg="(.*)", GString _skip = "");
	~GRegExp(void);
	void addOption(GRegExpOpt &opt);
	GVector<GString> *pregMatch(GString &str);
	static int isPos(GString str1, GString str2);
	static int isNPos(GString str1, GString str2, unsigned int pos);
	GString skipDouble(GString str);
	int longRes(GVector<GString> *res,unsigned int pos, unsigned int reg, GString &str);
	static bool isContener(GString str1, GString str2);
	GString getBurn() const;
	void setBurn(GString burn);
	GString BurnCorner(GString str);
	int burnLeft(GString str);
	int burnRight(GString str);

private:
	GVector<GRegExpOpt> _opt;
	GString _preg;
	GString _skip;
	GString _burn;
};

#endif
