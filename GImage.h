
#ifndef __GIMAGE_H__
# define __GIMAGE_H__

#include "GExport.h"
#include "GString.h"
#include "GFile.h"
#include "GStr.h"

struct GBitmapType
{
	char	file_type[2];
};

struct GBitmapHeaderFile
{
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
	int		bits_per_pixel : 16;
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

		unsigned int	Width(void) const;
		unsigned int	Height(void) const;
		GString			GetFormat(void) const;
		void			ConvertToJpeg(void);
		void			ConvertToBmp(const GString &FileName);
		
	private:
		GString			_file;
		unsigned int	_width;
		unsigned int	_height;
		GString			_format;
		GColorRVB		**_imageRVB;
		
};


#endif