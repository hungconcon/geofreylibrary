
#ifndef __GPROGRESSBAR_H__
# define __GPROGRESSBAR_H__

#include "GWidget.h"
#if defined(GWIN)
#	include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
#endif


class GProgressBar : public GWidget
{
	public:
		GProgressBar(GWidget *Parent);
		~GProgressBar(void);

		void	SetMinimum(unsigned int Minimum);
		void	SetMaximum(unsigned int Maximum);
		void	SetRange(unsigned int Minimum, unsigned int Maximum);
		void	SetValue(unsigned int Value);

	private:
		GWidget		*_parent;
};

#endif