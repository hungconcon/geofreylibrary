
#include "GWidget.h"

unsigned int GWidget::_id = 0;
GVector<GWidget *> GWidget::_vector;
GWidget::GWidget(void) : _min(0, 0), _max(0, 0), _actual(0, 0)
{
	this->_id = (this->_id)++;
	_vector.PushBack(this);
	this->_enabled = true;
}

GWidget::~GWidget(void)
{

}

void			GWidget::SetSize(void)
{
#if defined(GWIN)
	RECT lp;
	if (GetWindowRect(this->GetWidget(), &lp) != 0)
	{
		this->_actual.SetXY(lp.right - lp.left, lp.bottom - lp.top);
	}
#endif
}

GWidgetHandle	GWidget::GetWidget(void) const
{
	return (this->_widget);
}

void			GWidget::SetFont(const GFont &Font)
{
#if defined(GWIN)
	HFONT test = Font.GetFont();
	if (test == NULL)
		GMessageBox::Error("lala", "hihi");
	SendMessage(this->_widget, WM_SETFONT, (WPARAM)test, TRUE);
#endif
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

void			GWidget::SetWidth(unsigned int Width)
{
#if defined (GWIN)
	if (SetWindowPos(this->_widget, HWND_TOP, 0, 0, Width, this->_actual.GetY(), SWP_NOMOVE | SWP_NOOWNERZORDER) != 0)
		this->SetSize();
#endif	
}

void			GWidget::SetSize(const GSize &Size)
{
#if defined (GWIN)
	if (SetWindowPos(this->_widget, HWND_TOP, 0, 0, Size.GetX(), Size.GetY(), SWP_NOMOVE | SWP_NOOWNERZORDER) != 0)
		this->SetSize();
#endif	
}

void			GWidget::SetHeight(unsigned int Height)
{
#if defined (GWIN)
	if (SetWindowPos(this->_widget, HWND_TOP, 0, 0, this->_actual.GetX(), Height, SWP_NOMOVE | SWP_NOOWNERZORDER) != 0)
		this->SetSize();
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
#if defined (GWIN)
	EnableWindow(this->_widget, TRUE);
#endif
}

void			GWidget::Disable(void)
{
#if defined (GWIN)
	EnableWindow(this->_widget, FALSE);
#endif
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
#if defined(GWIN)
	if (SetWindowPos(this->_widget, HWND_TOP, X, Y, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER) != 0)
		;
#endif
}

void			GWidget::Move(const GSize &Size)
{
#if defined(GWIN)
	if (SetWindowPos(this->_widget, HWND_TOP, Size.GetX(), Size.GetY(), 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER) != 0)
		;
#endif
}

GWidget			*GWidget::GetWidgetByHandle(GWidgetHandle Handle)
{
	unsigned int i = 0;
	unsigned int size = _vector.Size();
	while (i < size)
	{
		GWidgetHandle test = _vector[i]->GetWidget(); 
		if (Handle == test)
			return (_vector[i]);
		++i;
	}
	return (NULL);
}

void	GWidget::SetBackgroundImage(const GString &Path)
{
#if defined(GWIN)
	PAINTSTRUCT paintst;
	BeginPaint(this->_widget, &paintst);
	Gdiplus::Graphics graphics(this->_widget);
	Gdiplus::Image image(L"C:\\fond.jpg");
	graphics.DrawImage(&image, 0, 0, image.GetWidth(), image.GetHeight());
	EndPaint(this->_widget, &paintst);
#endif
}
