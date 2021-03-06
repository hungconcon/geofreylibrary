
#include "GGroupBox.h"

#include <iostream>

GGroupBox::GGroupBox(const GString &Text, GWidget *Parent)
{
	this->_parent = Parent;
#if defined(GWIN)
	char	*tmp = Text.ToChar();
	this->_widget = CreateWindow("BUTTON", tmp, WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 0, 0, 100, 30, this->_parent->GetWidget(), NULL, NULL, NULL);
	delete[] tmp;
#endif
}

GGroupBox::GGroupBox(GWidget *Parent)
{
	this->_parent = Parent;
#if defined(GWIN)
	this->_widget = CreateWindow("BUTTON", "GGroupBox", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 0, 0, 100, 30, this->_parent->GetWidget(), NULL, NULL, NULL);
#endif
}


GGroupBox::~GGroupBox(void)
{
	
}

void	GGroupBox::SetText(const GString &Text)
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