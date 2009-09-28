
#include "GListBox.h"

#include <iostream>

GListBox::GListBox(const GWidget &Parent)
{
	this->_parent = Parent;
	this->_widget = CreateWindow("LISTBOX", "GGroupBox", WS_CHILD | WS_VISIBLE | WS_BORDER |LBS_NOTIFY,0, 0, 100, 30, this->_parent.GetWidget(), NULL, NULL, NULL);
}


GListBox::~GListBox(void)
{
	
}
