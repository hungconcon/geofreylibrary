
#include "GLineEdit.h"

#include <iostream>

GLineEdit::GLineEdit(GWidget *Parent)
{
	this->_parent = Parent;
#if defined(GWIN)
	this->_widget = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,0, 0, 100, 30, this->_parent->GetWidget(), NULL, NULL, NULL);
#endif
}


GLineEdit::~GLineEdit(void)
{
	
}

GString		GLineEdit::GetText(void)
{
	return (GString());
}

void		GLineEdit::SetText(const GString &Text)
{

}

void		GLineEdit::Password(void)
{
#if defined(GWIN)
	SendMessage(this->_widget, EM_SETPASSWORDCHAR, NULL, NULL);
#endif
}

void		GLineEdit::SetLimitLength(unsigned int Limit)
{
#if defined(GWIN)
	SendMessage(this->_widget, EM_SETLIMITTEXT,(WPARAM)Limit, NULL);
#endif
}

void		GLineEdit::SetPasswordChar(const GChar &Char)
{
#if defined(GWIN)
	SendMessage(this->_widget, EM_SETPASSWORDCHAR,(WPARAM)Char.GetChar(), NULL);
#endif	
}