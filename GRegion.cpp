
#include "GRegion.h"

GRegion::GRegion(void)
{
	this->_widget = NULL;
}

GRegion::~GRegion(void)
{

}

void	GRegion::Draw(void)
{
	


	//this->_region = CreateRectRgn(this->_position.GetX(), this->_position.GetY(), this->_position.GetX() + this->_size.GetX() * this->_sizeX, this->_position.GetY() + this->_size.GetY() * this->_sizeY);
	if (this->_region)
	{
		SetWindowRgn(this->_widget->GetWidget(), this->_region, TRUE);
	}
}

GSize			GRegion::GetSize(void) const
{
	return (this->_size);
}
unsigned int	GRegion::GetRow(void) const
{
	return (this->_numRow);
}
unsigned int	GRegion::GetCol(void) const
{
	return (this->_numCol);
}
void			GRegion::SetSpan(unsigned int X, unsigned int Y)
{
	this->_colspan = X;
	this->_rowspan = Y;
}

void			GRegion::SetElement(unsigned int X, unsigned int Y)
{
	this->_numCol = X;
	this->_numRow = Y;
}

void			GRegion::SetMargin(unsigned int Margin)
{
	this->_margin = Margin;
}

void			GRegion::SetParentSize(const GSize &Size)
{
	this->_parentSize = Size;
}
void			GRegion::SetWidget(GWidget *Widget)
{
	this->_widget = Widget;
}
void			GRegion::SetMax(unsigned int X, unsigned int Y)
{
	this->_maxCol = Y;
	this->_maxRow = X;
}