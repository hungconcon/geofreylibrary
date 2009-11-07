
#ifndef __GWINDOW_H__
# define __GWINDOW_H__

#include "GString.h"
#include "GSize.h"
#include "GFont.h"
#include "GMessageBox.h"
#include "GExport.h"
#include "GVector.hpp"

#if defined(GWIN)
#	include "windows.h"
#	include <gdiplus.h>
#	define STRICT
#pragma comment(lib, "gdiplus.lib")
typedef HWND GWidgetHandle;
#elif defined(GUNIX)
typedef int GWidgetHandle;
#endif

class GEXPORTED GWidget
{
	public:
		GWidget(void);
		~GWidget(void);
		GWidgetHandle	GetWidget(void) const;
		void			Show(void);
		void			Hide(void);
		void			SetHeight(unsigned int Height);
		void			SetWidth(unsigned int Width);
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
		static GWidget	*GetWidgetByHandle(GWidgetHandle);
		void			SetSize(void);
		void			SetSize(const GSize &Size);
		void			SetBackgroundImage(const GString &Image);
	
	protected:
		GWidgetHandle				_widget;
		bool						_enabled;
		GSize						_min;
		GSize						_max;
		GSize						_actual;
		static unsigned int			_id;
		static GVector<GWidget *>	_vector;
		
};

#endif