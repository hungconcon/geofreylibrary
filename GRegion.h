
#ifndef __GREGION_H__
#define __GREGION_H__

#include "GExport.h"
#include "GSize.h"
#include "GWidget.h"

#if defined(GWIN)
#		include "windows.h"
typedef HRGN GRegionType;
#endif

class GRegion
{
	public:
		GRegion(void);
		~GRegion(void);

		void		SetRegion(const GPoint &Point, const GSize &Size = GSize(1, 1));
		void		SetWidget(GWidget *Widget);
		void		SetMaxHeigthRegion(unsigned int MaxY);
		void		SetMaxWidthRegion(unsigned int MaxY);
		void		Draw(void);
		GPosition	GetPosition(void) const;

	private:
		GWidget			*_widget;
		GRegionType		_region;
		GPosition		_position;
		GSize			_size;
		unsigned int	_sizeX;
		unsigned int	_sizeY;
};

#endif