
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
		this->_format = "BMP";
		std::cout << " type du fichier   => " << HeaderFile.file_type[0] << HeaderFile.file_type[1] << std::endl;
		std::cout << " taile du fichier  => " << HeaderFile.file_size << std::endl;
		std::cout << " reserved          => " << HeaderFile.reserved << std::endl;
		std::cout << " bitmap offset     => " << HeaderFile.bitmap_offset << std::endl;
		GBitmapHeaderBitmap BitmapHeader;
		file.GoTo(file.CurrentIndex() - 2);
		file.Read(&BitmapHeader, sizeof(BitmapHeader));
		this->_width = BitmapHeader.width;
		this->_height = BitmapHeader.height;
		std::cout << " taille en tete    => " << BitmapHeader.header_size << std::endl;
		std::cout << " width             => " << BitmapHeader.width << std::endl;
		std::cout << " height            => " << BitmapHeader.height << std::endl;
		std::cout << " nb plan (1)       => " << BitmapHeader.planes << std::endl;
		std::cout << " profondeur        => " << BitmapHeader.compression << std::endl;
		std::cout << " size              => " << BitmapHeader.size_bitmap << std::endl;
		std::cout << " bpp               => " << BitmapHeader.bits_per_pixel << std::endl;
		std::cout << " res hor           => " << BitmapHeader.horiz_resolution << std::endl;
		std::cout << " res ver           => " << BitmapHeader.vert_resolution << std::endl;
		std::cout << " nb color          => " << BitmapHeader.colors_used << std::endl;
		std::cout << " color imp         => " << BitmapHeader.colors_important << std::endl;
		unsigned int line = this->_width * 3;
		while (line % 4 != 0)
			line++;
		this->_imageRVB = new GColorRVB*[this->_width];
		for (unsigned int i = 0; i < this->_width; ++i)
			this->_imageRVB[i] = new GColorRVB[this->_height];
		for (unsigned int j = 0; j < this->_height; ++j)
		{
			unsigned int i = 0;
			for (; i < this->_width; ++i)
			{
				file.Read(&this->_imageRVB[i][j], sizeof(GColorRVB));
			}
			if (i < line - i)
			{
				file.Read(line - i);
			}
		}
		file.Close();

	}
}

GImage::~GImage(void)
{

}

unsigned int	GImage::Height(void) const
{
	return (this->_height);
}

unsigned int	GImage::Width(void) const
{
	return (this->_width);
}

GString			GImage::GetFormat(void) const
{
	return (this->_format);
}

void			GImage::ConvertToBmp(const GString &FileName)
{
	GFile f(FileName);
	f.Open(true);
	GBitmapHeaderFile HeaderFile;
	GStrcpy(HeaderFile.file_type, "BM", 2);
	HeaderFile.reserved = 0;
	f.Write(&HeaderFile, sizeof(GBitmapHeaderFile));
	GBitmapHeaderBitmap BmpHeader;
	BmpHeader.header_size = 40;
	BmpHeader.width = this->_width;
	BmpHeader.height = this->_height;
	BmpHeader.planes = 1;
	BmpHeader.bits_per_pixel = 24;
	BmpHeader.compression = 0;
	BmpHeader.horiz_resolution = 0;
	BmpHeader.vert_resolution = 0;
	BmpHeader.colors_used = 0;
	BmpHeader.colors_important = 0;
	unsigned int line = this->_width * 3;
	while (line % 4 != 0)
		line++;
	BmpHeader.size_bitmap = line * this->_height;
	std::cout << BmpHeader.size_bitmap << std::endl;
	f.Write(&BmpHeader, sizeof(GBitmapHeaderBitmap));
	for (unsigned int j = 0; j < this->_height; ++j)
	{
		unsigned int i = 0;
		for (; i < this->_width; ++i)
		{
			f.Write(&this->_imageRVB[i][j], sizeof(GColorRVB));
		}
		if (i < line - 1)
		{
			char *buffer = new char[line - i];
			for (unsigned int k = 0; k < line - i; ++k)
				buffer[k] = 0;
			f.Write(&buffer, line - i);
			delete[] buffer;
		}
	}
	f.Close();
}

