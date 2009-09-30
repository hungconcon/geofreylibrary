
#ifndef __GGRIDLAYOUT_H__
# define __GGRIDLAYOUT_H__

#include "GWidget.h"
#include "GRegion.h"

class GGridLayout : public GWidget
{
	public:
		GGridLayout(GWidget *Parent);
		~GGridLayout(void);

		void	AddWidget(GWidget *Widget, unsigned int PositionX, unsigned int PositionY, unsigned int RowSpan = 1, unsigned int ColSpan = 1);
		void	SetMargin(unsigned int Margin);

	private:
		GWidget					*_parent;
		unsigned int			_margin;
		GVector<GRegion>		_region;
		GSize					_min;
};

#endif