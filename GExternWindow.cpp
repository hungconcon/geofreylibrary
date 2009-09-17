
#include "GExternWindow.h"

GExternWindow::GExternWindow(void)
{
	this->_handle = NULL;
}

GExternWindow::~GExternWindow(void)
{

}

bool	GExternWindow::Find(const GString &Name)
{
	char	*tmp = Name.ToChar();
	this->_handle = FindWindow(NULL, tmp);
	delete[] tmp;
	if (this->_handle == NULL)
		return (false);
	return (true);
}

bool	GExternWindow::SetTittle(const GString &Name)
{
	if (this->_handle)
	{
		bool	ok(true);
		char	*tmp = Name.ToChar();
		if (SetWindowText(this->_handle, tmp) == 0)
			ok = (false);
		delete[] tmp;
		return (ok);
	}
	return (false);
}

bool	GExternWindow::Hide(void)
{
	if (this->_handle)
	{
		if (ShowWindow(this->_handle, SW_HIDE) == 0)
			return (false);
		return (true);
	}
	return (false);
}

bool	GExternWindow::Show(void)
{
	if (this->_handle)
	{
		if (ShowWindow(this->_handle, SW_SHOW) == 0)
			return (false);
		return (true);
	}
	return (false);
}

bool	GExternWindow::IsVisible(void)
{
	if (this->_handle)
	{
		if (IsWindowVisible(this->_handle) == 0)
			return (false);
		return (true);
	}
	return (false);
}

bool	GExternWindow::Destroy(void)
{
	if (this->_handle)
	{
		if (DestroyWindow(this->_handle) == 0)
			return (false);
		return (true);
	}
	return (false);
}
