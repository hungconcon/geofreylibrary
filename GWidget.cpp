
#include "GWidget.h"

GWidget::GWidget(void)
{
	this->_enabled = true;
}

GWidget::~GWidget(void)
{

}

GWidgetHandle	GWidget::GetWidget(void) const
{
	return (this->_widget);
}

HINSTANCE		GWidget::GetHINCANCE(void) const
{
	return (this->_hInstance);
}
void			GWidget::Show(void)
{
#if defined (GWIN)
	ShowWindow(this->_widget, SW_SHOW);
#endif
}

void			GWidget::Hide(void)
{
#if defined (GWIN)
	ShowWindow(this->_widget, SW_HIDE);
#endif
}

void			GWidget::SetFixedSize(unsigned int X, unsigned int Y)
{
#if defined (GWIN)
	SetWindowPos(this->_widget, HWND_TOP, 0, 0, X, Y, SWP_NOMOVE | SWP_NOOWNERZORDER);
#endif
}
void			GWidget::SetFixedSize(const GSize &Size)
{
#if defined (GWIN)
	SetWindowPos(this->_widget, HWND_TOP, 0, 0, Size.GetX(), Size.GetY(), SWP_NOMOVE | SWP_NOOWNERZORDER);
#endif
}
void			GWidget::SetMaximumSize(unsigned int , unsigned int )
{

}
void			GWidget::SetMinimumSize(unsigned int X, unsigned int Y)
{
#if defined (GWIN)
	SetWindowPos(this->_widget, HWND_TOP, 0, 0, X, Y, SWP_NOMOVE | SWP_NOOWNERZORDER);
#endif
}

bool			GWidget::IsVisible(void)
{
#if defined (GWIN)
	if (IsWindowVisible(this->_widget) == 0)
		return (false);
#endif
	return (true);
}

bool			GWidget::IsEnabled(void) const
{
	return (this->_enabled);
}

void			GWidget::Enable(void)
{

}

void			GWidget::Disable(void)
{

}

GSize			GWidget::GetSize(void)
{
	//LPRECT lpRect;
	//GetWindowRect(this->_widget, lpRect);
	GSize s(300, 300);
	return (s);
}