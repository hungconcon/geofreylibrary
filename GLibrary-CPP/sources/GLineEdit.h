
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
		void		Password(void);
		void		SetPasswordChar(const GChar &Char);
		void		SetLimitLength(unsigned int Limit);


	private:
		GWidget		*_parent;
};

#endif