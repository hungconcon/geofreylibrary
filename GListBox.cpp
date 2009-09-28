
#include "GListBox.h"

#include <iostream>

GListBox::GListBox(GWidget *Parent)
{
	this->_parent = Parent;
	this->_widget = CreateWindow("LISTBOX", "GGroupBox", WS_CHILD | WS_VISIBLE | WS_BORDER |LBS_NOTIFY,0, 0, 100, 30, this->_parent->GetWidget(), NULL, NULL, NULL);
}


GListBox::~GListBox(void)
{
	
}

void		GListBox::AddItem(const GString &Item)
{
#if defined(GWIN)
	char *tmp = Item.ToChar();
	SendMessage(this->_widget, LB_ADDSTRING, 0, (LPARAM)tmp);
	delete[] tmp;
#endif
}
