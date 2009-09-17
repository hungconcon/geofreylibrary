
#ifndef __GIMAGE_H__
# define __GIMAGE_H__

#include "GExport.h"
#include "GString.h"
#include "GFile.h"

struct GBitmapHeaderFile
{
	char	file_type[2];
	int		file_size;
	int		reserved;
	int		bitmap_offset;
};

struct	GBitmapHeaderBitmap
{
	int		header_size;
	int		width;
	int		height;
	int		planes : 16;
	int		bits_per_pixe : 16;
	int		compression;
	int		size_bitmap;
	int		horiz_resolution;
	int		vert_resolution;
	int		colors_used;
	int		colors_important;
};

struct GColorRVB
{
	char	_red;
	char	_green;
	char	_blue;
};

class GEXPORTED GImage
{
	public:
		GImage(const GString &);
		GImage(void);
		~GImage(void);

		void	ConvertToJpeg(void);

	private:
		GString		_file;
		GColorRVB	**_imageRVB;
		
};


#endif