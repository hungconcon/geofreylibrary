
#include "FrenchDay.h"

FrenchDay::FrenchDay(void)
{
	this->_vec.PushBack("Dimanche");
	this->_vec.PushBack("Lundi");
	this->_vec.PushBack("Mardi");
	this->_vec.PushBack("Mercredi");
	this->_vec.PushBack("Jeudi");
	this->_vec.PushBack("Vendredi");
	this->_vec.PushBack("Samedi");
}

FrenchDay::~FrenchDay(void)
{
	
}

GString		FrenchDay::GetDay(unsigned int i)
{
	if (i < this->_vec.Size())
		return (this->_vec[i]);
	return (*(new GString("")));
}

GString		FrenchDay::GetTruncateDay(unsigned int i)
{
	if (i < this->_vec.Size())
		return (this->_vec[i].Substr(0, 3));
	return (*(new GString("")));
}
