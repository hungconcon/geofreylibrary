
#ifndef __GSLIDER_H__
# define __GSLIDER_H__

#include "GExport.h"
#include "GWidget.h"
#if defined(GWIN)
#	include <commctrl.h>
#endif


class GEXPORTED GSlider : public GWidget
{
	public:
		GSlider(GWidget *Parent);
		~GSlider(void);

	private:
		GWidget		*_parent;
};

#endif