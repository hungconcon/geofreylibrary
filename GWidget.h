
#ifndef __GWINDOW_H__
# define __GWINDOW_H__

#include "windows.h"
#include "GString.h"
#include "GSize.h"

typedef HWND GWidgetHandle;

class GWidget
{
	public:
		GWidgetHandle	GetWidget(void) const;
		HINSTANCE		GetHINCANCE(void) const;
		void			Show(void);
		void			Hide(void);
		void			SetFixedSize(unsigned int X, unsigned int Y);
		void			SetFixedSize(const GSize &Size);
		bool			IsVisible(void);

	protected:
		GWidgetHandle	_widget;
		HINSTANCE		_hInstance;
		
};

#endif