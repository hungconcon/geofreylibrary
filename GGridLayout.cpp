
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

void	GGridLayout::AddWidget(GWidget *Widget, unsigned int PositionX, unsigned int PositionY, unsigned int RowSpan, unsigned int ColSpan)
{
	if (Widget == NULL)
		return ;
	if (Widget->GetCurrentSize().GetX() > 0)
		this->_min.SetX(Widget->GetCurrentSize().GetX());
	if (Widget->GetCurrentSize().GetY() > 0)
		this->_min.SetY(Widget->GetCurrentSize().GetY());
	GSize Size = this->_parent->GetCurrentSize();
	unsigned int maxX = 0;
	unsigned int maxY = 0;
	unsigned int i = 0;
	while (i < this->_region.Size())
	{
		if (this->_region[i].GetRow() > maxX)
			maxX = this->_region[i].GetRow();
		if (this->_region[i].GetCol() > maxY)
			maxY = this->_region[i].GetCol();
		++i;
	}
	GRegion r;
	r.SetSpan(RowSpan, ColSpan);
	r.SetElement(PositionX, PositionY);
	r.SetMargin(this->_margin);
	r.SetParentSize(Size);
	r.SetWidget(Widget);
	r.SetMax(maxX, maxY);
	this->_region.PushBack(r);
	i = 0;
	while (i < this->_region.Size())
	{
		this->_region[i].Draw();
		++i;
	}
}

void	GGridLayout::SetMargin(unsigned int Margin)
{
	if (Margin == this->_margin)
		return ;
	this->_margin = Margin;
	unsigned int i = 0;
	while (i < this->_region.Size())
	{
		this->_region[i].SetMargin(this->_margin);
	}
}