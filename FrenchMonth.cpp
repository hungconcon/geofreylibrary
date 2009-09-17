
#include "FrenchMonth.h"

FrenchMonth::FrenchMonth(void)
{
	this->_vec.PushBack("Janvier");
	this->_vec.PushBack("Février");
	this->_vec.PushBack("Mars");
	this->_vec.PushBack("Avril");
	this->_vec.PushBack("Mai");
	this->_vec.PushBack("Juin");
	this->_vec.PushBack("Juillet");
	this->_vec.PushBack("Août");
	this->_vec.PushBack("Septembre");
	this->_vec.PushBack("Octobre");
	this->_vec.PushBack("Novembre");
	this->_vec.PushBack("Décembre");
}

FrenchMonth::~FrenchMonth(void)
{
	
}

GString		FrenchMonth::GetMonth(unsigned int i)
{
	if (i < this->_vec.Size())
		return (this->_vec[i]);
	return (*(new GString("")));
}

GString		FrenchMonth::GetTruncateMonth(unsigned int i)
{
	if (i < this->_vec.Size())
		return (this->_vec[i].Substr(0, 3));
	return (*(new GString("")));
}
