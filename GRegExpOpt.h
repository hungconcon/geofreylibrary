#ifndef GREGEXPOPT_H__
#define GREGEXPOPT_H__

#include "GString.h"

enum CaseSensi
{
NOSENS,
SENS,
};

enum PosEmpty
{
NOEMPTY,
EMPTY,
};

class GRegExpOpt
{
public:
	GRegExpOpt(const GString stopChar = "", PosEmpty emp = EMPTY, CaseSensi cas = SENS);
	GRegExpOpt(const GRegExpOpt &opt);
	~GRegExpOpt(void);
	void addObliWord(GString word);
	void addObliWord(GVector<GString> *word);

	void setCase(CaseSensi cas);
	void setEmp(PosEmpty emp);
	CaseSensi getCase() const;

	GVector<GString> getObliWord() const;
	GString getStopChar() const;
	PosEmpty getEmp() const;
	
	void setStopChar(GString _stopchar);
private:
	CaseSensi _case;
	GVector<GString> _obliWord;
	GString _stopChar;
	PosEmpty _emp;
};


#endif