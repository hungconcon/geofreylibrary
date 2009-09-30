
#ifndef __GGRIDLAYOUT_H__
# define __GGRIDLAYOUT_H__

#include "GWidget.h"
#include "GRegion.h"

class GGridLayout : public GWidget
{
	public:
		GGridLayout(GWidget *Parent);
		~GGridLayout(void);

		void	AddWidget(GWidget *Widget, unsigned int, unsigned int);
		void	AddWidget(GWidget *Widget, unsigned int, unsigned int, unsigned int, unsigned int);
		void	SetMargin(unsigned int Margin);
	private:
		GWidget					*_parent;
		unsigned int			_margin;
		GVector<GRegion>		_region;
		unsigned int			_sizeX;
		unsigned int
			_sizeY;
};

#endif