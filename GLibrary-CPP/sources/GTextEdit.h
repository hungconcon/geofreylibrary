
#ifndef __GTEXTEDIT_H__
# define __GTEXTEDIT_H__

#include "GWidget.h"
#if defined(GWIN)
#	include <Richedit.h>
#	include <commctrl.h>
#endif


class GTextEdit : public GWidget
{
	public:
		GTextEdit(GWidget *Parent);
		~GTextEdit(void);

		void	AddText(const GString &Text);

	private:
		GWidget		*_parent;
};

#endif