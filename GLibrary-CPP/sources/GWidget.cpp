
#include "GWidget.h"

GWidget::GWidget(void) : _min(0, 0), _max(0, 0), _actual(0, 0)
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
	if (SetWindowPos(this->_widget, HWND_TOP, 0, 0, X, Y, SWP_NOMOVE | SWP_NOOWNERZORDER) != 0)
	{
		this->_min.SetXY(X, Y);
		this->_max.SetXY(X, Y);
	}
#endif
}
void			GWidget::SetFixedSize(const GSize &Size)
{
#if defined (GWIN)
	if (SetWindowPos(this->_widget, HWND_TOP, 0, 0, Size.GetX(), Size.GetY(), SWP_NOMOVE | SWP_NOOWNERZORDER) != 0)
	{
		this->_min = Size;
		this->_max = Size;
	}
#endif
}
void			GWidget::SetMaximumSize(unsigned int X, unsigned int Y)
{
	this->_max.SetXY(X, Y);
}

void			GWidget::SetMaximumSize(const GSize &Size)
{
	this->_max = Size;
}
void			GWidget::SetMinimumSize(unsigned int X, unsigned int Y)
{
	
#if defined (GWIN)
	if (SetWindowPos(this->_widget, HWND_TOP, 0, 0, X, Y, SWP_NOMOVE | SWP_NOOWNERZORDER) != 0)
		this->_min.SetXY(X, Y);
#endif
}
void			GWidget::SetMinimumSize(const GSize &Size)
{
#if defined (GWIN)
	if (SetWindowPos(this->_widget, HWND_TOP, 0, 0, Size.GetX(), Size.GetY(), SWP_NOMOVE | SWP_NOOWNERZORDER) != 0)
		this->_min = Size;
#endif
}
void			GWidget::SetMaximumHeight(unsigned int MaxHeight)
{
	this->_max.SetY(MaxHeight);
}
void			GWidget::SetMaximumWidth(unsigned int MaxWidth)
{
	this->_max.SetX(MaxWidth);
}
void			GWidget::SetMinimumHeight(unsigned int MinHeight)
{
	this->_min.SetY(MinHeight);
}
void			GWidget::SetMinimumWidth(unsigned int MinWidth)
{
	this->_min.SetX(MinWidth);
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

GSize			GWidget::GetCurrentSize(void) const
{
	return (this->_actual);
}

GSize			GWidget::GetMinimumSize(void) const
{
	return (this->_min);
}

GSize			GWidget::GetMaximumSize(void) const
{
	return (this->_max);
}
unsigned int	GWidget::GetMaximumHeight(void) const
{
	return (this->_max.GetY());
}
unsigned int	GWidget::GetMaximumWidth(void) const
{
	return (this->_max.GetX());
}
unsigned int	GWidget::GetMinimumHeight(void) const
{
	return (this->_min.GetY());
}
unsigned int	GWidget::GetMinimumWidth(void) const
{
	return (this->_min.GetX());
}


void			GWidget::Move(unsigned int X, unsigned int Y)
{
	if (SetWindowPos(this->_widget, HWND_TOP, X, Y, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER) != 0)
		;

}

void			GWidget::Move(const GSize &Size)
{
	if (SetWindowPos(this->_widget, HWND_TOP, Size.GetX(), Size.GetY(), 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER) != 0)
		;

}