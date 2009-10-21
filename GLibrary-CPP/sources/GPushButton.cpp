
#include "GPushButton.h"

#include <iostream>

GPushButton::GPushButton(const GString &Text, GWidget *Parent)
{
	this->_parent = Parent;
#if defined(GWIN)
	char	*tmp = Text.ToChar();
	this->_widget = CreateWindow("BUTTON", tmp, WS_CHILD | DS_NOFAILCREATE | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, 100, 30, this->_parent->GetWidget(), NULL, NULL, NULL);
	delete[] tmp;
#endif
}

GPushButton::GPushButton(GWidget *Parent)
{
	this->_parent = Parent;
#if defined(GWIN)
	this->_widget = CreateWindow("BUTTON", "GPushButton", WS_CHILD | DS_NOFAILCREATE | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, 100, 30, this->_parent->GetWidget(), NULL, NULL, NULL);
#endif
}


GPushButton::~GPushButton(void)
{
	
}

void	GPushButton::SetText(const GString &Text)
{
#if defined (GWIN)
	char	*tmp = Text.ToChar();
	if (SendMessage(this->_widget, WM_SETTEXT, NULL, (LPARAM)tmp) == 0)
	{
		delete[] tmp;
		throw GException("GPushButton", "Canot set Text !");
	}
	delete[]tmp;
#endif
}