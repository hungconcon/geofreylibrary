
#ifndef __GGRIDLAYOUT_H__
# define __GGRIDLAYOUT_H__

#include "GWidget.h"

class GGridLayout : public GWidget
{
	public:
		GGridLayout(GWidget *Parent);
		~GGridLayout(void);

		void	AddWidget(GWidget *Widget, unsigned int, unsigned int);
		void	AddWidget(GWidget *Widget, unsigned int, unsigned int, unsigned int, unsigned int);

	private:
		GWidget		*_parent;
};

#endif