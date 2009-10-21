
#ifndef __GPUSHBUTTON_H__
# define __GPUSHBUTTON_H__

#include "GWidget.h"
#include "GExport.h"

class GEXPORTED GPushButton : public GWidget
{
	public:
		GPushButton(GWidget *Parent);
		GPushButton(const GString &Text, GWidget *Parent);
		~GPushButton(void);

		void	SetText(const GString &Text);

	
	private:
		GWidget		*_parent;
};

#endif