
#include "GTextEdit.h"

#include <iostream>

GTextEdit::GTextEdit(GWidget *Parent)
{
	this->_parent = Parent;
	//this->_widget = CreateWindow("BUTTON", "GGroupBox", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 0, 0, 100, 30, this->_parent->GetWidget(), NULL, NULL, NULL);
}


GTextEdit::~GTextEdit(void)
{
	
}

void	GTextEdit::AddText(const GString &Text)
{

}