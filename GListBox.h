
#ifndef __GLISTBOX_H__
# define __GLISTBOX_H__

#include "GWidget.h"

class GListBox : public GWidget
{
	public:
		GListBox(const GWidget &Parent);
		~GListBox(void);


	
	private:
		GWidget		_parent;
};

#endif