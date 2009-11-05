
#ifndef __GTABWIDGET_H__
# define __GTABWIDGET_H__

#include "GWidget.h"
#include "GExport.h"

#if defined(GWIN)
#	include <commctrl.h>
#endif

class GEXPORTED GTabWidget : public GWidget
{
	public:
		GTabWidget(GWidget *Widget);
		~GTabWidget(void);

	private:
		GWidget		*_parent;
};

#endif