
#include "GWebCamViewer.h"

GWebCamViewer::GWebCamViewer(void)
{
	this->_wcActive = false;
}

GWebCamViewer::~GWebCamViewer(void)
{

}

bool	GWebCamViewer::Connect(const GWidget &Parent, short Width, short Height)
{
	this->_parent = Parent;
	this->_widget = capCreateCaptureWindow("handle", WS_VISIBLE | WS_CHILD, 0, 0, Width, Height, this->_parent.GetWidget(), 1);
	if (this->_widget == NULL)
		return (false);
	if (!capDriverConnect(this->_widget, 0))
		return (false);
	this->_hDC_WC = GetDC(this->_widget);
	return (true);
}

void	GWebCamViewer::Disconnect(void)
{
	capDriverDisconnect(this->_widget);
	this->_wcActive = false;
} 

bool	GWebCamViewer::IsActive(void) const
{
	return (this->_wcActive);
}

void	GWebCamViewer::CaptureImage(const GString &File)
{
	capCaptureSingleFrameOpen(this->_widget);
	capCaptureSingleFrame(this->_widget);
	capCaptureSingleFrameClose(this->_widget);
	char	*tmp =  File.ToChar();
	capFileSaveDIB(this->_widget, tmp);
	delete[] tmp;
} 

void	GWebCamViewer::StartDisplay(void)
{
	capPreviewScale(this->_widget, TRUE);
	capPreviewRate(this->_widget, 15);
	capPreview(this->_widget, 1);
	this->_wcActive = TRUE;
} 

void	GWebCamViewer::StartRecord(const GString &File)
{
	//capDlgVideoCompression(this->_widget);
	char	*tmp = File.ToChar();
	capFileSetCaptureFile(this->_widget, tmp);
	delete[] tmp;
	capCaptureSequence(this->_widget);
	this->_wcActive = true;
} 

void	GWebCamViewer::StopRecord(void)
{
	capCaptureStop(this->_widget); 
}