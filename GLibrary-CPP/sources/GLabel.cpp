
#include "GLabel.h"

#include <iostream>

GLabel::GLabel(GWidget *Parent)
{
	this->_parent = Parent;
}

GLabel::GLabel(const GString &, GWidget *Parent)
{
	this->_parent = Parent;
}

GLabel::~GLabel(void)
{
	
}

GString		GLabel::GetText(void)
{
	return (GString());
}

void		GLabel::SetText(const GString &Text)
{

}
