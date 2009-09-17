
#ifndef __GPUSHBUTTON_H__
# define __GPUSHBUTTON_H__

#include "GWidget.h"

class GPushButton : public GWidget
{
	public:
		GPushButton(const GWidget &Parent);
		GPushButton(const GString &Text, const GWidget &Parent);
		~GPushButton(void);

		void	SetText(const GString &Text);

	
	private:
		GWidget		_parent;
};

#endif