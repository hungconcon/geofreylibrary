
#ifndef __GWEBCAMVIWER_H__
# define __GWEBCAMVIWER_H__

#include "GString.h"
#include "GWidget.h"
#include <windows.h>
#include <vfw.h>

#pragma comment(lib, "vfw32.lib")
#define MAX_IMAGE 5

struct Pixel
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
	int Couleur;
};

struct	BitMap
{
	int largeur;
	int hauteur;
	Pixel** points;
}; 

class GWebCamViewer : public GWidget
{
	public:
		GWebCamViewer(void);
		~GWebCamViewer(void);

		bool	Connect(const GWidget &Parent, short Largeur, short Hauteur);
		void	Disconnect(void);
		bool	IsActive(void) const;
		void	CaptureImage(const GString &FileName);
		void	StartDisplay(void);		
		void	StartRecord(const GString &Name);
		void	StopRecord(void);
	

/* // Fonction qui gère la webcam
  BOOL ChooseSource();
 
 void AfficheWebCam();
 void StopConnect();
 
 void SaveImgFile(char *fichier);
 void DriverInfo();

 // Variable
 */
 
 HDC hDC;

	private:
		GWidget	_parent;
		bool	_wcActive;
		HWND	_handle;
		HDC		_hDC_WC;
};

#endif

