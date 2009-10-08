
#include "GExternWindow.h"

GExternWindow::GExternWindow(void)
{
	this->_widget = NULL;
}

GExternWindow::~GExternWindow(void)
{

}

bool	GExternWindow::Find(const GString &Name)
{
	char	*tmp = Name.ToChar();
	this->_widget = FindWindow(NULL, tmp);
	delete[] tmp;
	if (this->_widget == NULL)
		return (false);
	return (true);
}

bool	GExternWindow::SetTittle(const GString &Name)
{
	if (this->_widget)
	{
		bool	ok(true);
		char	*tmp = Name.ToChar();
		if (SetWindowText(this->_widget, tmp) == 0)
			ok = (false);
		delete[] tmp;
		return (ok);
	}
	return (false);
}

