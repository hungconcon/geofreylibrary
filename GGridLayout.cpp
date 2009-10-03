
#include "GGridLayout.h"

#include <iostream>

GGridLayout::GGridLayout(GWidget *Parent) 
{
	this->_parent = Parent;
	this->_marginX = 5;
	this->_marginY = 5;
	this->_maxX = 0;
	this->_maxY = 0;
	this->_parentSize = this->_parent->GetCurrentSize();
}

GGridLayout::~GGridLayout(void)
{
	
}

void	GGridLayout::AddWidget(GWidget *Widget, unsigned int PositionX, unsigned int PositionY, unsigned int RowSpan, unsigned int ColSpan)
{
	if (Widget == NULL)
		return ;
	if (PositionX > this->_maxX)
		this->_maxX = PositionX;
	if (PositionY > this->_maxY)
		this->_maxY = PositionY;
	if (ColSpan == 1 && RowSpan == 1)
	{
		this->CalculColumnMin(PositionY, Widget);
		this->CalculRowMin(PositionX, Widget);
	}
	GUIntMap col = this->GetColumn();
	GUIntMap row = this->GetRow();
	unsigned int i = 0;
	while (i < this->_region.Size())
	{
		if (this->_region[i]._region != NULL)
		{
			DeleteObject(this->_region[i]._region);
		}
		GSize Start = this->GetPositionStart(this->_region[i], col, row);
		GSize End = this->GetPositionEnd(this->_region[i], col, row);
		this->_region[i]._region = CreateRectRgn(Start.GetX(), Start.GetY(), End.GetX(), End.GetY());
		if (this->_region[i]._region)
		{
			SetWindowRgn(this->_region[i]._widget->GetWidget(), this->_region[i]._region, TRUE);
		}
		
		++i;
	}

}

void	GGridLayout::SetMargin(unsigned int Margin)
{
	if (Margin == this->_marginX && Margin == this->_marginY)
		return ;
	this->_marginX = Margin;
	this->_marginY = Margin;
}

void	GGridLayout::SetVerticalMargin(unsigned int MarginX)
{
	this->_marginX = MarginX;
}

void	GGridLayout::SetHorizontalMargin(unsigned int MarginY)
{
	this->_marginY = MarginY;
}

void	GGridLayout::CalculColumnMin(unsigned int Position, GWidget *Widget)
{
	if (this->_col.ExistKey(Position))
	{
		if (Widget->GetMinimumWidth() > this->_col[Position])
			this->_col[Position] = Widget->GetMinimumWidth();
	}
	else
	{
		this->_col[Position] = Widget->GetMinimumWidth();
	}
}

void	GGridLayout::CalculRowMin(unsigned int Position, GWidget *Widget)
{
	if (this->_col.ExistKey(Position))
	{
		if (Widget->GetMinimumHeight() > this->_col[Position])
			this->_col[Position] = Widget->GetMinimumHeight();
	}
	else
	{
		this->_col[Position] = Widget->GetMinimumHeight();
	}
}

GSize	GGridLayout::GetPositionStart(GStructRegion s, GUIntMap X, GUIntMap Y)
{
	unsigned int XStart = 0;
	unsigned int YStart = 0;
	unsigned int i = 0;
	XStart += this->_marginX;
	while (i < s._posY)
	{
		XStart += X[i];
		XStart += this->_marginX;
		++i;
	}
	i = 0;
	YStart += this->_marginY;
	while (i < s._posX)
	{
		YStart += Y[i];
		YStart += this->_marginY;
		++i;
	}
	return (GSize(XStart, YStart));
}

GSize	GGridLayout::GetPositionEnd(GStructRegion s, GUIntMap X, GUIntMap Y)
{
	unsigned int XStart = 0;
	unsigned int YStart = 0;
	unsigned int i = 0;
	XStart += this->_marginX;
	while (i < s._posY)
	{
		XStart += X[i];
		XStart += this->_marginX;
		++i;
	}
	XStart += X[i];
	i = 0;
	YStart += this->_marginY;
	while (i < s._posX)
	{
		YStart += Y[i];
		YStart += this->_marginY;
		++i;
	}
	YStart += Y[i];
	return (GSize(XStart, YStart));
}

GUIntMap	GGridLayout::GetColumn(void)
{
	return (this->_col);
}

GUIntMap	GGridLayout::GetRow(void)
{
	return (this->_row);
}