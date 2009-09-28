
#ifndef __GLINEEDIT_H__
# define __GLINEEDIT_H__

#include "GWidget.h"

class GLineEdit : public GWidget
{
	public:
		GLineEdit(GWidget *Parent);
		~GLineEdit(void);

		GString		GetText(void);
		void		SetText(const GString &Text);

	private:
		GWidget		*_parent;
};

#endif