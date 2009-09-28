
#include "GProgressBar.h"

#include <iostream>


GProgressBar::GProgressBar(GWidget *Parent)
{
	this->_parent = Parent;
	this->_widget = CreateWindow("PROGRESS_CLASS", NULL, WS_CHILD | WS_VISIBLE, 0, 0, 100, 30, this->_parent->GetWidget(), NULL, NULL, NULL);
}


GProgressBar::~GProgressBar(void)
{
	
}

void	GProgressBar::SetMinimum(unsigned int Minimum)
{

}

void	GProgressBar::SetMaximum(unsigned int Maximum)
{

}

void	GProgressBar::SetRange(unsigned int Minimum, unsigned int Maximum)
{

}

void	GProgressBar::SetValue(unsigned int Value)
{

}