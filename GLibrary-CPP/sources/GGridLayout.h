
#ifndef __GGRIDLAYOUT_H__
# define __GGRIDLAYOUT_H__

#include "GWidget.h"
#include "GMap.hpp"

#if defined(GWIN)
#		include "windows.h"
typedef HRGN GRegionType;
#endif

struct GStructRegion
{
	GStructRegion(GWidget *Widget, unsigned int X, unsigned int Y, unsigned int col, unsigned int row) : _widget(Widget), _posX(X), _posY(Y), _colspan(col), _rowspan(row){}
	GWidget			*_widget;
	unsigned int	_posX;
	unsigned int	_posY;
	unsigned int	_colspan;
	unsigned int	_rowspan;
};


class GGridLayout : public GWidget
{
	public:
		GGridLayout(GWidget *Parent);
		~GGridLayout(void);

		void	AddWidget(GWidget *Widget, unsigned int PositionX, unsigned int PositionY, unsigned int RowSpan = 1, unsigned int ColSpan = 1);
		void	SetMargin(unsigned int Margin);
		void	SetVerticalMargin(unsigned int Margin);
		void	SetHorizontalMargin(unsigned int Margin);

	private:
		GWidget					*_parent;
		GSize					_parentSize;
		unsigned int			_marginX;
		unsigned int			_marginY;
		GVector<GStructRegion>	_region;
		unsigned int			_maxX;
		unsigned int			_maxY;
		GUIntMap				_col;
		GUIntMap				_row;

		void		CalculColumnMin(unsigned int X, GWidget *Widget);
		void		CalculRowMin(unsigned int X, GWidget *Widget);
		GUIntMap	GetColumn(void);
		GUIntMap	GetRow(void);
		GSize		GetPositionStart(GStructRegion, GUIntMap, GUIntMap);
		GSize		GetPositionEnd(GStructRegion, GUIntMap, GUIntMap);
};

#endif