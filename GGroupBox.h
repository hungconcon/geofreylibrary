
#ifndef __GGROUPBOX_H__
# define __GGROUPBOX_H__

#include "GWidget.h"

class GGroupBox : public GWidget
{
	public:
		GGroupBox(GWidget *Parent);
		GGroupBox(const GString &Text, GWidget *Parent);
		~GGroupBox(void);

		void	SetText(const GString &Text);

	
	private:
		GWidget		*_parent;
};

#endif