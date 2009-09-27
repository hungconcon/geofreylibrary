
#include "GImage.h"
#include "GSwap.hpp"

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
		this->_imageRGB = new GColorRGB*[this->_width];
		for (unsigned int i = 0; i < this->_width; ++i)
			this->_imageRGB[i] = new GColorRGB[this->_height];
		for (unsigned int j = 0; j < this->_height; ++j)
		{
			unsigned int i = 0;
			for (; i < this->_width; ++i)
				file.Read(&this->_imageRGB[i][j], sizeof(GColorRGB));
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
	Type.file_type[0] = 'B';
	Type.file_type[1] = 'M';
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
	unsigned int j = 0;
	for (; j < this->_height; ++j)
	{
		unsigned int i = 0;
		for (; i < this->_width; ++i)
			f.Write(&this->_imageRGB[i][j], sizeof(GColorRGB));
		if ((i * 3) < line)	
		{
			GString	Empty(GString::GetBuffer("\0", 1));
			GString	str;
			for (; (i * 3) < line; i++)
				str += Empty;
			f.Write(str);
		}
		if (this->_height % 4 != 0)
			f.Write(GString::GetBuffer("\0\0", 2));
	}
	f.Close();
}

void			GImage::MirrorVertical(void)
{
	for (unsigned int i = 0; i < this->_width / 2; ++i)
		for (unsigned int j = 0; j < this->_height; ++j)
		{
			GSwap(this->_imageRGB[i][j], this->_imageRGB[this->_width - i - 1][j]);
		}
}

void			GImage::MirrorHorizontal(void)
{
	for (unsigned int i = 0; i < this->_width; ++i)
		for (unsigned int j = 0; j < this->_height / 2; ++j)
		{
			GSwap(this->_imageRGB[i][j], this->_imageRGB[i][this->_height - j]);
		}
}

void			GImage::Rotation(void)
{
	this->MirrorVertical();
	this->MirrorHorizontal();
}

void			GImage::RotationLeft(void)
{
	GColorRGB	**tmp = new GColorRGB*[this->_height];
	for (unsigned int i = 0; i < this->_height; ++i)
		tmp[i] = new GColorRGB[this->_width];

	/*
	for (unsigned int j = 0; j < this->_height; ++j)
		for (unsigned int i = 0; i < this->_width; ++i)
			tmp[j][i] = this->_imageRVB[i][j];
	*/

	for (unsigned int i = 0; i < this->_width; ++i)
		delete[] this->_imageRGB[i];
	delete[] this->_imageRGB;
	this->_imageRGB = tmp;
	
	GSwap(this->_height, this->_width);
}

void			GImage::RotationRight(void)
{
}

