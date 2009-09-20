#include <iostream>
#include "GRegExpOpt.h"

using namespace std;

GRegExpOpt::GRegExpOpt(const GString stopChar, PosEmpty emp,CaseSensi cas)
{
	_stopChar = GString(stopChar);
	_case = cas;
	_obliWord = GVector<GString>();
	_emp = emp;
}

GRegExpOpt::~GRegExpOpt(void)
{

}

GRegExpOpt::GRegExpOpt(const GRegExpOpt &opt)
{
	this->_case = opt._case;
	this->_emp = opt._emp;
	this->_obliWord = opt._obliWord;
	this->_stopChar = opt._stopChar;
}


void GRegExpOpt::addObliWord(GString word)
{
	_obliWord.PushFront(word);
}

void GRegExpOpt::addObliWord(GVector<GString> *word)
{
	for (unsigned int i = 0; i < word->Size();i++)
	{
		_obliWord.PushFront((*word)[i]);
	}
}


void GRegExpOpt::setCase(CaseSensi cas)
{
	_case = cas;
}
	
CaseSensi GRegExpOpt::getCase() const
{
	return _case;
}

GVector<GString> GRegExpOpt::getObliWord() const
{
	return _obliWord;
}
	
GString GRegExpOpt::getStopChar() const
{
	return _stopChar;
}
	
void GRegExpOpt::setStopChar(GString stopchar)
{
	_stopChar = GString(stopchar);
}

void GRegExpOpt::setEmp(PosEmpty emp)
{
	_emp = emp;
}

PosEmpty GRegExpOpt::getEmp() const
{
	return _emp;
}
