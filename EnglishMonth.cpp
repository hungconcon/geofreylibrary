
#include "EnglishMonth.h"

EnglishMonth::EnglishMonth(void)
{
	this->_vec.PushBack("January");
	this->_vec.PushBack("February");
	this->_vec.PushBack("March");
	this->_vec.PushBack("April");
	this->_vec.PushBack("May");
	this->_vec.PushBack("June");
	this->_vec.PushBack("July");
	this->_vec.PushBack("August");
	this->_vec.PushBack("September");
	this->_vec.PushBack("October");
	this->_vec.PushBack("November");
	this->_vec.PushBack("December");
}

EnglishMonth::~EnglishMonth(void)
{
	
}

GString		EnglishMonth::GetMonth(unsigned int i)
{
	if (i < this->_vec.Size())
		return (this->_vec[i]);
	return (GString(""));
}

GString		EnglishMonth::GetTruncateMonth(unsigned int i)
{
	if (i < this->_vec.Size())
		return (this->_vec[i].Substr(0, 3));
	return (GString(""));
}
