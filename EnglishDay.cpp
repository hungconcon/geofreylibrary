
#include "EnglishDay.h"

EnglishDay::EnglishDay(void)
{
	this->_vec.PushBack("Sunday");
	this->_vec.PushBack("Monday");
	this->_vec.PushBack("Tuesday");
	this->_vec.PushBack("Wednesday");
	this->_vec.PushBack("Thursday");
	this->_vec.PushBack("Friday");
	this->_vec.PushBack("Saturday");
}

EnglishDay::~EnglishDay(void)
{
	
}

GString		EnglishDay::GetDay(unsigned int i)
{
	if (i < this->_vec.Size())
		return (this->_vec[i]);
	return (new GString(""));
}

GString		EnglishDay::GetTruncateDay(unsigned int i)
{
	if (i < this->_vec.Size())
		return (this->_vec[i].Substr(0, 3));
	return (new GString(""));
}
