
#include "GTextEdit.h"

#include <iostream>

GTextEdit::GTextEdit(GWidget *Parent)
{
	this->_parent = Parent;
	LoadLibrary("RICHED32.DLL");
	this->_widget = CreateWindow(RICHEDIT_CLASS, "", WS_CHILD | WS_VISIBLE | WS_BORDER, 0, 0, 100, 30, this->_parent->GetWidget(), NULL, NULL, NULL);
}


GTextEdit::~GTextEdit(void)
{
	
}

void	GTextEdit::AddText(const GString &Text)
{

}