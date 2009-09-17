
#include "GImage.h"

GImage::GImage(const GString &File) : _file(File)
{
	if (this->_file.EndWith(".bmp"))
	{
		this->_file = File;
		GFile file(this->_file);
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
		file.GoTo(file.CurrentIndex() - 2);
		file.Read(&BitmapHeader, sizeof(BitmapHeader));
		std::cout << " taille en tete    => " << BitmapHeader.header_size << std::endl;
		std::cout << " width             => " << BitmapHeader.width << std::endl;
		std::cout << " height            => " << BitmapHeader.height << std::endl;
		std::cout << " nb plan (1)       => " << BitmapHeader.planes << std::endl;
		std::cout << " profondeur        => " << BitmapHeader.compression << std::endl;
		std::cout << " size              => " << BitmapHeader.size_bitmap << std::endl;
		std::cout << " res hor           => " << BitmapHeader.horiz_resolution << std::endl;
		std::cout << " res ver           => " << BitmapHeader.vert_resolution << std::endl;
		std::cout << " nb color          => " << BitmapHeader.colors_used << std::endl;
		std::cout << " color imp         => " << BitmapHeader.colors_important << std::endl;
		file.Close();
	}
}

GImage::~GImage(void)
{

}