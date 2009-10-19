
#ifndef __GFONT_H__
#define __GFONT_H__

#include "GExport.h"
#include "GString.h"

#if defined(GWIN)
typedef HFONT GFontType;
#endif

class GEXPORTED GFont
{
	public:
		GFont(void);
		GFont(const GFont &Font);
		GFont(const GString &Family, unsigned int Size = 12, unsigned int Weight = Normal, bool Italic = false);
		~GFont(void);

		void	SetFamily(const GString &Family);
		void	SetUnderline(bool Underline);
		void	SetWeigth(unsigned int Weigth);
		void	SetItalic(bool Italic);
		void	SetSize(unsigned int Size);
		void	SetStrikeOut(bool Strike);
		
		bool			IsStrickeOut(void) const;
		bool			IsBold(void) const;
		bool			IsItalic(void) const;
		bool			IsUnderline(void) const;
		unsigned int	GetSize(void) const;
		unsigned int	GetWeight(void) const;
		GString			GetFamily(void) const;
		GFontType		GetFont(void) const;


		enum FontWeigth
		{
			Invisible	= 0,
			Thin		= 100,
			ExtraLight	= 200,
			Light		= 300,
			Normal		= 400,
			Medium		= 500,
			SemiBold	= 600,
			Bold		= 700,
			ExtraBold	= 800,
			Black		= 900
		};

	private:
		GString		_family;
		int			_size;
		int			_weight;
		bool		_underline;
		bool		_italic;
		bool		_barre;
		GFontType	_font;

		void	MAJ(void);
};

#endif