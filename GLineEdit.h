
#ifndef __GLINEEDIT_H__
# define __GLINEEDIT_H__

#include "GWidget.h"

class GLineEdit : public GWidget
{
	public:
		GLineEdit(const GWidget &Parent);
		~GLineEdit(void);

	private:
		GWidget		_parent;
};

#endif