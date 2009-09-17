
struct GBitmapHeaderFile
{
	char	file_type[2];
	int		file_size;
	int		reserved;
	int		bitmap_offset
};

struct	GBitmapHeaderBitmap
{
	int		header_size;
	int		width;
	int		height;
	int		planes : 2 (16);
	int		bits_per_pixe; : 2 (16);
	int		compression;
	int		size_bitmap;
	int		horiz_resolution;
	int		vert_resolution;
	int		colors_used;
	int		colors_important;
};