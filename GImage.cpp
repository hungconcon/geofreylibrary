
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
		GBitmapHeaderFile	HeaderFile;
		GBitmapType			Type;
		file.Read(&Type, sizeof(Type));
		file.Read(&HeaderFile, sizeof(HeaderFile));
		this->_format = "BMP";
		std::cout << " type du fichier   => " << Type.file_type[0] << Type.file_type[1] << std::endl;
		std::cout << " taile du fichier  => " << HeaderFile.file_size << std::endl;
		std::cout << " reserved          => " << HeaderFile.reserved << std::endl;
		std::cout << " bitmap offset     => " << HeaderFile.bitmap_offset << std::endl;
		GBitmapHeaderBitmap BitmapHeader;
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
				file.Read(&this->_imageRVB[i][j], sizeof(GColorRVB));
			while ((i * 3) < line)
				file.Read(line - (i++ * 3));
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
	f.Clear();
	f.Open(true);
	GBitmapHeaderFile	HeaderFile;
	GBitmapType			Type;
	GStrcpy(Type.file_type, "BM", 2);
	HeaderFile.reserved = 0;
	HeaderFile.bitmap_offset = 54;
	
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
	HeaderFile.file_size = BmpHeader.size_bitmap;

	f.Write(&Type, sizeof(Type));
	f.Write(&HeaderFile, sizeof(HeaderFile));
	f.Write(&BmpHeader, sizeof(BmpHeader));
	for (unsigned int j = 0; j < this->_height; ++j)
	{
		unsigned int i = 0;
		for (; i < this->_width; ++i)
			f.Write(&this->_imageRVB[i][j], sizeof(GColorRVB));
		if (i < line)	
		{
			GString	Empty(GString::GetBuffer("\0", 1));
			GString	str;
			for (; i * 3 < line; i++)
				str += Empty;
			f.Write(str);
		}
	}
	f.Close();
}

