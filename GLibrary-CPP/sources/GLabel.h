
#ifndef __GLABEL_H__
# define __GLABEL_H__

#include "GWidget.h"

class GLabel : public GWidget
{
	public:
		GLabel(GWidget *Parent);
		GLabel(const GString &Text, GWidget *Parent);
		~GLabel(void);

		GString		GetText(void);
		void		SetText(const GString &Text);

	private:
		GWidget		*_parent;
};

#endif