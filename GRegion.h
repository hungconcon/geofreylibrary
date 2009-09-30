
#ifndef __GREGION_H__
#define __GREGION_H__

#include "GExport.h"
#include "GSize.h"
#include "GWidget.h"

#if defined(GWIN)
#		include "windows.h"
typedef HRGN GRegionType;
#endif

class GRegion
{
	public:
		GRegion(void);
		~GRegion(void);

		void			Draw(void);
		void			SetParentSize(const GSize &Size);
		void			SetMargin(unsigned int Margin);
		void			SetSpan(unsigned int X, unsigned int Y);
		void			SetElement(unsigned int X, unsigned int Y);
		void			SetWidget(GWidget *Widget);
		void			SetMax(unsigned int X, unsigned int Y);
		GSize			GetSize(void) const;
		unsigned int	GRegion::GetCol(void) const;
		unsigned int	GRegion::GetRow(void) const;


	private:
		GWidget			*_widget;
		GRegionType		_region;
		GSize			_size;
		GSize			_parentSize;
		unsigned int	_colspan;
		unsigned int	_rowspan;
		unsigned int	_numCol;
		unsigned int	_numRow;
		unsigned int	_margin;
		unsigned int	_maxCol;
		unsigned int	_maxRow;
};

#endif