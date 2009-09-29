
#ifndef __GSTRING_H__
# define __GSTRING_H__

#include "GVector.hpp"

#include <string>
#include <iostream>
#include <stdarg.h>
#include "GChar.h"
#include "GException.h"
#include "GWarning.h"
#include "GExport.h"
#include "GMap.hpp"

#if defined (WIN32) | defined (_WIN32) |  defined (__WIN32) | defined (WIN64) | defined (__WIN64)
#		include "atlbase.h"
#		include "atlstr.h"
#		include "comutil.h"
#else
#		include "string.h"
#endif

#define TRUEGSTR "true"
#define FALSEGSTR "false"

/* 
Informations :
DescriptionFr : 
Classe de gestion des chaines de caratères.
DescriptionEn : 
String class functions.
*/

class GEXPORTED GString
{
	public:
		enum CaseOption
		{
			CaseSensitive,
			CaseInsensitive
		};

		GString(void);
		GString(const char *Str);
		GString(const GString &);
		GString(const GString *);
		GString(bool Booleen);
		GString(const std::string &Str);
		GString(const GChar &);
		GString(const GChar *);
		#if defined (WIN32) | defined (_WIN32) |  defined (__WIN32) | defined (WIN) | defined (WIN64) | defined (__WIN64)
		GString(const std::wstring &);
		GString(const wchar_t *);
		GString(const CString &);
		#endif
		GString(char);											
		GString(unsigned char);									
		GString(int Number);
		GString(unsigned int Number);
		GString(long Number);
		GString(unsigned long Number);
		GString(short Number);
		GString(unsigned short Number);
		GString(float Number, unsigned int Precision = 6);
		GString(double Number, unsigned int Precision = 6);
		GString(long long Number, unsigned int Precision = 6);
		~GString(void);

		// --== CONVERSIONS ==--

		#if defined (WIN32) | defined (_WIN32) |  defined (__WIN32) | defined (WIN) | defined (WIN64) | defined (__WIN64)
		std::wstring	ToWString(void) const;
		wchar_t			*ToWChar_t(void) const;
		CString			ToCString(void) const;
		LPCSTR			ToLPCSTR(void) const;
		#endif
		bool			ToBool(void) const;
		std::string		ToStdString(void) const;
		char			*ToChar(void) const;
		int				ToInt(void) const;
		double			ToDouble(void) const;

		// --== SURCHARGES ==--

		bool					operator==(const GString &) const;
		bool					operator!=(const GString &) const;
		GString					&operator=(const GString &);
		GString					&operator+=(const GString &);
		friend GString			operator+(const char *, const GString &);
		friend GString			operator+(const GString &, const char *);
		friend GString			operator+(const GString &, const GString &);
		char					operator[](unsigned int) const;
		bool					operator>(const GString &) const;
		bool					operator<(const GString &) const;
		bool					Contain(const GString &, CaseOption = GString::CaseSensitive) const;
		friend	std::ostream	&operator<<(std::ostream &out, const GString &);
		friend	std::ostream	&operator<<(std::ostream &out, const GString *);
		friend	std::istream	&operator>>(std::istream &flux, GString &m);
		
		// --== METHODES ==--
		static GString		GetString(GString Format, ...);
		unsigned int		Length(void) const;														
		unsigned int		Size(void) const;
		unsigned int		Count(const GString &, CaseOption = GString::CaseSensitive) const;
		int					FirstIndexOfChar(char, G::IndexOption = G::INDEX_ALL_CHAR) const;
		int					LastIndexOfChar(char, G::IndexOption = G::INDEX_ALL_CHAR) const;
		int					FirstIndexOf(const GString &, GString::CaseOption = GString::CaseSensitive) const;				
		int					LastIndexOf(const GString &, GString::CaseOption = GString::CaseSensitive) const;
		int					FirstIndexOfChar(char, char, G::IndexOption = G::INDEX_ALL_CHAR) const;
		int					LastIndexOfChar(char, char, G::IndexOption = G::INDEX_ALL_CHAR) const;
		int					Find(const GString &, CaseOption = GString::CaseSensitive) const;
		int					Find(const GString &, unsigned int, CaseOption = GString::CaseSensitive) const;			
		bool				IsNumeric(void) const;
		bool				Compare(const GString &Str) const;
		bool				IsAlpha(void) const;
		bool				EndWith(const GString &Str) const;
		bool				StartWith(const GString &Str) const;
		bool				IsEmpty(void) const;
		static GString		GetBuffer(const char *, unsigned int);
		static GString		Join(GVector<GString> &List, const GString &, G::SplitOption = G::SKIP_EMPTY_PARTS);
		static GString		Join(GVector<GString> &List, G::SplitOption = G::SKIP_EMPTY_PARTS);
		static GString		Implode(GVector<GString> &List, const GString &, G::SplitOption = G::SKIP_EMPTY_PARTS);
		static GString		Implode(GVector<GString> &List, G::SplitOption = G::SKIP_EMPTY_PARTS);
		GString				Remove(unsigned int, unsigned int) const;
		GString				Remove(const GString &, CaseOption = GString::CaseSensitive) const;
		GString				Fill(char) const;														
		GString				Fill(char, unsigned int) const;	
		GString				GetMiddleString(const GString &, const GString &, CaseOption = GString::CaseSensitive) const;
		GString				GetRightString(const GString &Start, CaseOption = GString::CaseSensitive) const;
		GString				GetLeftString(const GString &Start, CaseOption = GString::CaseSensitive) const;
		GString				ToUpper(void) const;
		GString				ToLower(void) const;
		GString				Substr(unsigned int, unsigned int) const;
		GString				Substr(unsigned int) const;
		GString				RightJustified(unsigned int, char = ' ') const;
		GString				LeftJustified(unsigned int, char = ' ') const;
		GString				Insert(unsigned int, const GString &) const;
		GString				Replace(const GString &, const GString &, CaseOption = GString::CaseSensitive) const;
		GString				RightTrim(G::TrimOption c = G::TRIM_BLANK) const;
		GString				LeftTrim(G::TrimOption c = G::TRIM_BLANK) const;
		GString				Trim(G::TrimOption c = G::TRIM_BLANK) const;
		GString				Printable(void) const;
		GString				Reverse(void) const;
		GVector<GString>	Split(const GString &, G::SplitOption = G::SKIP_EMPTY_PARTS , CaseOption = GString::CaseSensitive) const;
		GVector<GString>	Explode(const GString &, G::SplitOption = G::SKIP_EMPTY_PARTS , CaseOption = GString::CaseSensitive) const;
		void				Clear(void);
		void				Truncate(unsigned int);

		
		static int	NotFound;

	private:
		char			*_str;
		unsigned int	_size;
		unsigned int	_allocate;
		static GString	GetContent(const char *, unsigned int);
};

typedef GVector<GString> GStringList;
typedef GMap<GString, GString> GStringMap;

#endif
