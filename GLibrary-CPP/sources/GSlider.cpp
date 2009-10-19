
#include "GSlider.h"

GSlider::GSlider(GWidget *Parent)
{
	this->_parent = Parent;
	this->_widget = CreateWindow(TRACKBAR_CLASS, "", WS_CHILD | WS_VISIBLE | TBS_NOTICKS, 0, 0, 300, 20, this->_parent->GetWidget(), NULL, NULL, NULL);
}

GSlider::~GSlider(void)
{

}