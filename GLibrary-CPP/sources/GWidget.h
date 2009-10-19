
#ifndef __GWINDOW_H__
# define __GWINDOW_H__

#include "windows.h"
#include "GString.h"
#include "GSize.h"
#include "GFont.h"
#include "GMessageBox.h"

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
		void			SetMinimumWidth(unsigned int X);
		void			SetMinimumHeight(unsigned int Y);
		void			SetMaximumSize(unsigned int X, unsigned int Y);
		void			SetMaximumSize(const GSize &Size);
		void			SetMaximumWidth(unsigned int X);
		void			SetMaximumHeight(unsigned int Y);
		GSize			GetCurrentSize(void) const;
		GSize			GetMinimumSize(void) const;
		GSize			GetMaximumSize(void) const;
		unsigned int	GetMinimumWidth(void) const;
		unsigned int	GetMinimumHeight(void) const;
		unsigned int	GetMaximumWidth(void) const;
		unsigned int	GetMaximumHeight(void) const;
		void			Move(unsigned int X, unsigned Y);
		void			Move(const GSize &Size);
		bool			IsVisible(void);
		bool			IsEnabled(void) const;
		void			Enable(void);
		void			Disable(void);
		void			SetFont(const GFont &Font);

	protected:
		GWidgetHandle	_widget;
		HINSTANCE		_hInstance;
		bool			_enabled;
		GSize			_min;
		GSize			_max;
		GSize			_actual;		
};

#endif