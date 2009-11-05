
#include "GTabWidget.h"

GTabWidget::GTabWidget(GWidget *Parent)
{
	this->_parent = Parent;
#if defined(GWIN)
	this->_widget = CreateWindow(WC_TABCONTROL, "", WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE, 0, 0, 100, 100, this->_parent->GetWidget(), NULL, NULL, NULL);
#endif
}

GTabWidget::~GTabWidget(void)
{

}