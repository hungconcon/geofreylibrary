
#include "GImage.h"

void	GImage::BitmapToRVBMatrix(const GString &File)
{
	GFile file(File);
	file.Open(true);
	if (!file.IsOpen())
		return ;
	GBitmapHeaderFile HeaderFile;
	file.Read(&HeaderFile, sizeof(HeaderFile));
	std::cout << " type du fichier   => " << HeaderFile.file_type[0] << HeaderFile.file_type[1] << std::endl;
	std::cout << " taile du fichier  => " << HeaderFile.file_size << std::endl;
	std::cout << " reserved          => " << HeaderFile.reserved << std::endl;
	std::cout << " bitmap offset     => " << HeaderFile.bitmap_offset << std::endl;
	GBitmapHeaderBitmap BitmapHeader;
	file.Read(&BitmapHeader, sizeof(BitmapHeader));
	std::cout << " width             => " << BitmapHeader.width << std::endl;
	std::cout << " height            => " << BitmapHeader.height << std::endl;
	file.Close();
}