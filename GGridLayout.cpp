
#include "GGridLayout.h"

#include <iostream>

GGridLayout::GGridLayout(GWidget *Parent)
{
	this->_parent = Parent;
	this->_margin = 5;
}


GGridLayout::~GGridLayout(void)
{
	
}

void	GGridLayout::AddWidget(GWidget *Widget, unsigned int PositionX, unsigned int PositionY)
{
	GSize ParentSize = this->_parent->GetSize();
	unsigned int maxX = 0;


}

void	GGridLayout::AddWidget(GWidget *Widget, unsigned int, unsigned int, unsigned int, unsigned int )
{

}

void	GGridLayout::SetMargin(unsigned int Margin)
{
	this->_margin = Margin;
}