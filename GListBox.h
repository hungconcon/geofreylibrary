
#ifndef __GLISTBOX_H__
# define __GLISTBOX_H__

#include "GWidget.h"

class GListBox : public GWidget
{
	public:
		GListBox(GWidget *Parent);
		~GListBox(void);

		void	AddItem(const GString &Item);


	
	private:
		GWidget		*_parent;
};

#endif