
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
#if defined(GWIN)
	SETTEXTEX str;
	str.codepage = CP_ACP;
	str.flags = ST_KEEPUNDO;
	SendMessage(this->GetWidget(), EM_SETTEXTEX, (WPARAM)&str, (LPARAM)Text.ToLPCSTR());	
#endif
}

void	GTextEdit::SetText(const GString &Text)
{
#if defined(GWIN)
	SETTEXTEX str;
	str.codepage = CP_ACP;
	str.flags = ST_DEFAULT;
	SendMessage(this->GetWidget(), EM_SETTEXTEX, (WPARAM)&str, (LPARAM)Text.ToLPCSTR());	
#endif
}

void	GTextEdit::Clear(void)
{
#if defined(GWIN)
	SETTEXTEX str;
	str.codepage = CP_ACP;
	str.flags = ST_DEFAULT;
	SendMessage(this->GetWidget(), EM_SETTEXTEX, (WPARAM)&str, (LPARAM)"");	
#endif
}