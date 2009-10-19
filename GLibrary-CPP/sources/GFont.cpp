
#include "GFont.h"

GFont::GFont(void)
{
	this->_underline = false;
	this->_family = "Arial";
	this->_italic = false;
	this->_barre = false;
	this->_size = 12;
	this->_weight = 400;
	this->MAJ();
}

GFont::GFont(const GString &Family, unsigned int Size, unsigned int Weight, bool Italic)
{
	if (Size > 300)
		Size = 300;
	if (Size < 1)
		Size = 1;
	if (Weight > 900)
		Weight = 900;
	this->_underline = false;
	this->_family = Family;
	this->_italic = Italic;
	this->_barre = false;
	this->_size = Size;
	this->_weight = Weight;
	this->MAJ();
}
GFontType		GFont::GetFont(void) const
{
	return (this->_font);
}
void			GFont::SetStrikeOut(bool Strike)
{
	this->_barre = Strike;
	this->MAJ();
}
bool			GFont::IsStrickeOut(void) const
{
	return (this->_barre);
}

GFont::GFont(const GFont &Font)
{
	this->_underline = Font._underline;
	this->_family = Font._family;
	this->_italic = Font._italic;
	this->_barre = Font._barre;
	this->_size = Font._size;
	this->_weight = Font._weight;
	this->MAJ();
}

void	GFont::MAJ(void)
{
	if (this->_font)
    {
        DeleteObject(this->_font);
        this->_font = CreateFont(this->_size, 0, 0, 0, this->_weight, this->_italic, this->_underline, this->_barre, ANSI_CHARSET, 0, 0, 0, 0, this->_family.ToLPCSTR());
    }
}



GFont::~GFont(void)
{
	if (this->_font)
    {
        DeleteObject(this->_font);
	}
}

void	GFont::SetItalic(bool Italic)
{
	this->_italic = Italic;
	this->MAJ();
}
void	GFont::SetFamily(const GString &Family)
{
	this->_family = Family;
	this->MAJ();
}
void	GFont::SetSize(unsigned int Size)
{
	if (Size > 300)
		Size = 300;
	if (Size < 1)
		Size = 1;
	this->_size = Size;
	this->MAJ();
}
unsigned int	GFont::GetSize(void) const
{
	return (this->_size);
}
GString			GFont::GetFamily(void) const
{
	return (this->_family);
}
unsigned int	GFont::GetWeight(void) const
{
	return (this->_weight);
}
void	GFont::SetUnderline(bool Underline)
{
	this->_underline = Underline;
	this->MAJ();
}
void	GFont::SetWeigth(unsigned int Weight)
{
	if (Weight > 900)
		Weight = 900;
	this->_weight = Weight;
	this->MAJ();
}
bool	GFont::IsItalic(void) const
{
	return (this->_italic);
}
bool	GFont::IsUnderline(void) const
{
	return (this->_underline);
}
bool	GFont::IsBold(void) const
{
	if (this->_weight >= 700)
		return (true);
	return (false);
}
