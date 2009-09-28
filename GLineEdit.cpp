
#include "GLineEdit.h"

#include <iostream>

GLineEdit::GLineEdit(const GWidget &Parent)
{
	this->_parent = Parent;
	this->_widget = CreateWindow("EDIT", "GGroupBox", WS_CHILD | WS_VISIBLE,0, 0, 100, 30, this->_parent.GetWidget(), NULL, NULL, NULL);
}


GLineEdit::~GLineEdit(void)
{
	
}
