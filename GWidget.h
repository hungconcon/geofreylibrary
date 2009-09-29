
#ifndef __GWINDOW_H__
# define __GWINDOW_H__

#include "windows.h"
#include "GString.h"
#include "GSize.h"

typedef HWND GWidgetHandle;

class GWidget
{
	public:
		GWidget(void);
		~GWidget(void);
		GWidgetHandle	GetWidget(void) const;
		HINSTANCE		GetHINCANCE(void) const;
		void			Show(void);
		void			Hide(void);
		void			SetFixedSize(unsigned int X, unsigned int Y);
		void			SetFixedSize(const GSize &Size);
		void			SetMinimumSize(unsigned int X, unsigned int Y);
		void			SetMinimumSize(const GSize &Size);
		void			SetMaximumSize(unsigned int X, unsigned int Y);
		void			SetMaximumSize(const GSize &Size);
		bool			IsVisible(void);
		bool			IsEnabled(void) const;
		void			Enable(void);
		void			Disable(void);
		GSize			GetSize(void);

	protected:
		GWidgetHandle	_widget;
		HINSTANCE		_hInstance;
		bool			_enabled;
		
};

#endif