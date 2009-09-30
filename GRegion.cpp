
#include "GRegion.h"

GRegion::GRegion(void)
{
	this->_widget = NULL;
}

GRegion::~GRegion(void)
{

}

void	GRegion::SetRegion(const GPoint &Point, const GSize &Size)
{
	this->_size = Size;
	this->_position = Point;
}

GPosition	GRegion::GetPosition(void) const
{
	return (this->_position);
}

void	GRegion::SetWidget(GWidget *Widget)
{
	if (this->_region)
	{
		SetWindowRgn(Widget->GetWidget(), this->_region, TRUE);
	}
}

void	GRegion::SetMaxWidthRegion(unsigned int MaxX)
{
	this->_sizeX = MaxX;
}

void	GRegion::SetMaxHeigthRegion(unsigned int MaxY)
{
	this->_sizeY = MaxY;
}

void	GRegion::Draw(void)
{
	this->_region = CreateRectRgn(this->_position.GetX(), this->_position.GetY(), this->_position.GetX() + this->_size.GetX() * this->_sizeX, this->_position.GetY() + this->_size.GetY() * this->_sizeY);
}