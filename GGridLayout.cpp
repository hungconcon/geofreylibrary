
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
	unsigned int maxY = 0;
	unsigned int i = 0;
	while (i < this->_region.Size())
	{
		if (this->_region[i].GetPosition().GetX() > maxX)
			maxX = this->_region[i].GetPosition().GetX();
		if (this->_region[i].GetPosition().GetY() > maxY)
			maxY = this->_region[i].GetPosition().GetY();
		++i;
	}
	unsigned int maxHeight = ParentSize.GetY() / (maxY + 1);
	unsigned int maxWidth = ParentSize.GetX() / (maxX + 1);
	GRegion r;
	r.SetRegion(GPoint(PositionX, PositionY));
	this->_region.PushBack(r);
	i = 0;
	while (i < this->_region.Size())
	{
		this->_region[i].SetMaxHeigthRegion(maxHeight);
		this->_region[i].SetMaxWidthRegion(maxWidth);
		this->_region[i].Draw();
		++i;
	}


}

void	GGridLayout::AddWidget(GWidget *Widget, unsigned int, unsigned int, unsigned int, unsigned int )
{

}

void	GGridLayout::SetMargin(unsigned int Margin)
{
	this->_margin = Margin;
}