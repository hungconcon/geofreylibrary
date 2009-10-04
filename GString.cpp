
#include "GString.h"
#include "GWarning.h"


#include <iostream>
using std::cerr;
using std::endl;


#define	SIZE	20

// CONSTRUCTEURS

int		GString::NotFound = -1;


GString::GString(void)
{
	this->_size = 0;
	this->_allocate = this->_size + SIZE;
	this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
	this->_str[0] = 0;
}

GString::GString(const char *str)
{
	if (str == NULL)
	{
		GWarning::Warning("GString", "GString(const char *)", "Pointer is Null");
		this->_size = 0;
		this->_allocate = this->_size + SIZE;
		this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
		this->_str[0] = 0;
		return ;
	}
	this->_size = 0;
	while (str[this->_size])
		this->_size++;
	this->_allocate = this->_size + SIZE;
	this->_str = new char[this->_allocate + 2];
	for (unsigned int i = 0; i < this->_size + 1; ++i)
		this->_str[i] = str[i];
}

GString::GString(const GString &s)
{
	std::cout << "SIZE => " << s._size << std::endl;
	this->_size = s._size;
	this->_allocate = this->_size + SIZE;
	unsigned int alloc = ((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1;
	std::cout << "ALLOCATE : " << alloc << std::endl;
	this->_str = new char[alloc];
	for (unsigned int i = 0; i < this->_size + 1; ++i)
		this->_str[i] = s._str[i];
}

GString::GString(const GString *s)
{
	this->_allocate = s->_allocate;
	this->_size = s->_size;
	this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
	for (unsigned int i = 0; i < this->_size + 1; ++i)
		this->_str[i] = s->_str[i];
}

GString::GString(bool test)
{
	if (test == true)
	{
		this->_size = 4;
		this->_allocate = this->_size + SIZE;
		this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
		
		for (unsigned int i = 0; i < this->_size; i++)
			this->_str[i] = TRUEGSTR[i];
		this->_str[this->_size] = 0;
	}
	else
	{
		this->_size = 5;
		this->_allocate = this->_size + SIZE;
		this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
		for (unsigned int i = 0; i < this->_size; i++)
			this->_str[i] = TRUEGSTR[i];
		this->_str[this->_size] = 0;
	}
}

GString::GString(const std::string &s)
{
	this->_size = 0;
	unsigned int size = strlen(s.c_str());
	unsigned int i = 0;
	for (; i < size && s[i] != 0; ++i)
		if (GChar(s[i]).IsPrintable())
			this->_size++;
	this->_allocate = this->_size + SIZE;
	this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
	for (i = 0; i < size && s[i] != 0; ++i)
		if (GChar(s[i]).IsPrintable())
			this->_str[i] = s[i];
	this->_str[i] = 0;
}

GString::GString(const GChar &c)
{
	this->_str = new char[2];
	this->_str[0] = c.GetChar();
	this->_str[1] = 0;
	this->_size = 1;
}

GString::GString(const GChar *c)
{
	this->_size = 1;
	this->_allocate = this->_size + SIZE;
	this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
	this->_str[0] = c->GetChar();
	this->_str[1] = 0;
}

GString::GString(char c)
{
	this->_size = 1;
	this->_allocate = this->_size + SIZE;
	this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
	this->_str[0] = c;
	this->_str[1] = 0;
}

GString::GString(unsigned char c)
{
	this->_size = 1;
	this->_allocate = this->_size + SIZE;
	this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
	this->_str = new char[2];
	this->_str[0] = c;
	this->_str[1] = 0;
}

#if defined (WIN32) | defined (_WIN32) |  defined (__WIN32) | defined (WIN) | defined (WIN64) | defined (__WIN64)
GString::GString(const std::wstring &wstr)
{
	this->_size = wstr.size();
	this->_allocate = this->_size + SIZE;
	this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
	unsigned int i = 0;
	for (; i < this->_size + 1; ++i)
		this->_str[i] = (char)wstr[i];
	this->_str[i] = 0;
}

GString::GString(const wchar_t *str)
{
	unsigned int i = 0;
	while(str[i])
		i++;
	this->_size = i;
	this->_allocate = this->_size + SIZE;
	this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
	for (unsigned int i = 0; i < this->_size + 1; ++i)
		this->_str[i] = (char)str[i];
}

GString::GString(const CString &s)
{
	this->_size = s.GetLength();
	char	*tmp = (char*)LPCTSTR(s);
	this->_size = s.GetLength();
	this->_allocate = this->_size + SIZE;
	this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
	unsigned int i = 0;
	for (; i < this->_size; i++)
		this->_str[i] = tmp[i];
	this->_str[i] = 0;
}

#endif
GString::~GString(void)
{
	delete[] this->_str;
}

GString::GString(float nbr, unsigned int precision)
{
	if (precision > 9)
		precision = 9;
	float save = nbr;
	unsigned int i = 0;
	while ((int)save > 0)
	{
		save /= 10;
		i++;
	}
	save = nbr;
	this->_size = i + precision + 1;
	this->_allocate = this->_size + SIZE;
	this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
	i = 0;
	for (; (int)save > 0; ++i)
	{
		this->_str[this->_size - i - 1 - precision - 1] = ((int)save % 10) + '0';
		save /= 10;
	}
	this->_str[i++] = '.';
	save = nbr - (int)nbr;
	for (unsigned int j = 0; j < precision; ++j, ++i)
	{	
		save *= 10;
		this->_str[i] = ((int)save % 10) + '0';
	}	
	this->_str[i] = 0;
}

GString::GString(double nbr, unsigned int precision)
{
	if (precision > 9)
		precision = 9;
	double save = nbr;
	unsigned int i = 0;
	while ((int)save > 0)
	{
		save /= 10;
		i++;
	}
	save = nbr;
	this->_size = i + precision + 1;
	this->_allocate = this->_size + SIZE;
	this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
	i = 0;
	for (; (int)save > 0; ++i)
	{
		this->_str[this->_size - i - 1 - precision - 1] = ((int)save % 10) + '0';
		save /= 10;
	}
	this->_str[i++] = '.';
	save = nbr - (int)nbr;
	for (unsigned int j = 0; j < precision; ++j, ++i)
	{	
		save *= 10;
		this->_str[i] = ((int)save % 10) + '0';
	}	
	this->_str[i] = 0;
}

GString::GString(long long nbr, unsigned int precision)
{
	if (precision > 9)
		precision = 9;
	long long save(nbr);
	unsigned int i = 0;
	while ((int)save > 0)
	{
		save /= 10;
		i++;
	}
	save = nbr;
	if (precision == 0)
		this->_size = i + precision;
	else 
		this->_size = i + precision + 1;
	this->_allocate = this->_size + SIZE;
	this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
	i = 0;
	for (; (int)save > 0; ++i)
	{
		this->_str[this->_size - i - 1 - precision - 1] = ((int)save % 10) + '0';
		save /= 10;
	}
	if (precision != 0)
	{
		this->_str[i++] = '.';
		save = nbr - (int)nbr;
		for (unsigned int j = 0; j < precision; ++j, ++i)
		{	
			save *= 10;
			this->_str[i] = (save % 10) + '0';
		}
	}
	else
	{
		this->_str[i - 1] = 0;
		this->_size = this->_size - 1;
	}
	this->_str[i] = 0;
}

GString::GString(int nbr)
{
	if (nbr == 0)
	{
		this->_size = 1;
		this->_str = new char[2];
		this->_str[0] = '0';
		this->_str[1] = 0;
		return ;
	}
	int saveNbr = nbr;
	bool isNeg = false;
	this->_size = 0;
	if (nbr < 0)
	{
		isNeg = true;
		nbr *= -1;
		saveNbr *= -1;
		this->_size++;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		this->_size++;
	}
	this->_allocate = this->_size + SIZE;
	this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
	if (isNeg == true)
		this->_str[0] = '-';
	for (unsigned int i = 0; i < this->_size && saveNbr > 0; ++i)
	{
		this->_str[this->_size - i - 1] = (saveNbr % 10) + '0';
		saveNbr /= 10;
	}
	this->_str[this->_size] = 0;
}

GString::GString(unsigned int nbr)
{
	if (nbr == 0)
	{
		this->_size = 1;
		this->_str = new char[2];
		this->_str[0] = '0';
		this->_str[1] = 0;
		return ;
	}
	unsigned int saveNbr = nbr;
	this->_size = 0;
	while (nbr > 0)
	{
		nbr /= 10;
		this->_size++;
	}
	this->_allocate = this->_size + SIZE;
	this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
	for (unsigned int i = 0; i < this->_size && saveNbr > 0; ++i)
	{
		this->_str[this->_size - i - 1] = (saveNbr % 10) + '0';
		saveNbr /= 10;
	}
	this->_str[this->_size] = 0;
}

GString::GString(short nbr)
{
	short saveNbr = nbr;
	bool isNeg = false;
	this->_size = 0;
	if (nbr < 0)
	{
		isNeg = true;
		nbr *= -1;
		saveNbr *= -1;
		this->_size++;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		this->_size++;
	}
	this->_allocate = this->_size + SIZE;
	this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
	if (isNeg == true)
		this->_str[0] = '-';
	for (unsigned int i = 0; i < this->_size && saveNbr > 0; ++i)
	{
		this->_str[this->_size - i - 1] = (saveNbr % 10) + '0';
		saveNbr /= 10;
	}
	this->_str[this->_size] = 0;
}

GString::GString(unsigned short nbr)
{
	unsigned short saveNbr = nbr;
	this->_size = 0;
	while (nbr > 0)
	{
		nbr /= 10;
		this->_size++;
	}
	this->_allocate = this->_size + SIZE;
	this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
	for (unsigned int i = 0; i < this->_size && saveNbr > 0; ++i)
	{
		this->_str[this->_size - i - 1] = (saveNbr % 10) + '0';
		saveNbr /= 10;
	}
	this->_str[this->_size] = 0;
}

GString::GString(long nbr)
{
	long saveNbr = nbr;
	bool isNeg = false;
	this->_size = 0;
	if (nbr < 0)
	{
		isNeg = true;
		nbr *= -1;
		saveNbr *= -1;
		this->_size++;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		this->_size++;
	}
	this->_allocate = this->_size + SIZE;
	this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
	if (isNeg == true)
		this->_str[0] = '-';
	for (unsigned int i = 0; i < this->_size && saveNbr > 0; ++i)
	{
		this->_str[this->_size - i - 1] = (saveNbr % 10) + '0';
		saveNbr /= 10;
	}
	this->_str[this->_size] = 0;
}

GString::GString(unsigned long nbr)
{
	unsigned long saveNbr = nbr;
	this->_size = 0;
	while (nbr > 0)
	{
		nbr /= 10;
		this->_size++;
	}
	this->_allocate = this->_size + SIZE;
	this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
	for (unsigned int i = 0; i < this->_size && saveNbr > 0; ++i)
	{
		this->_str[this->_size - i - 1] = (saveNbr % 10) + '0';
		saveNbr /= 10;
	}
	this->_str[this->_size] = 0;
}
// METHODE
GString				GString::GetBuffer(const char *str, unsigned int size)
{
	GString s;
	delete[] s._str;
	s._size = size;
	s._allocate = s._size + SIZE;
	s._str = new char[s._allocate + 1];
	unsigned int i = 0;
	for (; i < size; ++i)
		s._str[i] = str[i];
	s._str[i] = 0;
	return (s);
}

GString				GString::GetContent(const char *str, unsigned int size)
{
	GString s(GString::GetBuffer(str, size));
	delete[] str;
	return (s);
}

unsigned int		GString::Length(void) const
{
	return (this->_size);
}

unsigned int		GString::Size(void) const
{
	return (this->_size);
}

unsigned int		GString::Count(const GString &find, CaseOption op) const
{
	int pos = 0;
	int nbr = 0;
	while (true)
	{
		pos = this->Find(find, pos, op);
		if (pos == -1)
			return (nbr);
		nbr++;
		pos += find.Size();
	}
}

int					GString::LastIndexOfChar(char c , G::IndexOption op) const
{
	if (op == G::INDEX_ALL_CHAR)
	{
		for (int i = this->Length() - 1; i > 0; --i)
		{
			if (this->_str[i] == c)
				return (i);
		}
	}
	else if (op == G::INDEX_THIS_CHAR)
	{
		for (int i = this->Length() - 1; i > 0; --i)
		{
			if (this->_str[i] != c)
				return (i - 1);
		}
	}
	return (-1);
}

int					GString::LastIndexOfChar(char b , char e, G::IndexOption op) const
{
	for (unsigned int i = this->Length() - 1; i > 0; ++i)
	{
		if (op == G::INDEX_ALL_CHAR)
		{
			if (this->_str[i] >= b && this->_str[i] <= e)
				return (i);
		}
		else if (op == G::INDEX_THIS_CHAR)
		{
			if (this->_str[i] < b || this->_str[i] > e)
			return (i - 1);
		}
	}
	return (-1);
}

GString				GString::Printable(void) const
{
	GString s;
	delete[] s._str;
	s._allocate = this->_size + SIZE;
	s._str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
	unsigned int j = 0;
	for (unsigned int i = 0; s < this->_size; ++i)
	{
		GChar c(this->_str[i]);
		if (c.IsPrintable())
			s._str[j++] = this->_str[i];
	}
	s._str[j] = 0;
	s._size = j;
	return (s);
}

GString				GString::GetString(GString Format, ...)
{
	va_list ap;
	GString f(Format);
	va_start(ap, Format);
	GString str;
	GString t;
	for (unsigned int i = 0; i < f._size; ++i)
	{
		if (f[i] == '%')
		{
			i++;
			switch (f[i])
			{
				case 'i' :
					t = va_arg(ap, int);
					break;
				case 'l' :
					t = va_arg(ap, long);
					break;
				case 'f' :
					t = va_arg(ap, double);
					break;
				case 's' :
					t = va_arg(ap, char*);
					break;
#if defined (GWIN)
				case 'g' :
					t = va_arg(ap, GString);
					break;
#endif
				case '%' :
					t = "%";
					break;
				default :
					throw GException("GString", "Bad GetString format !");
					break;
			}
			str += t;
		}
		else
			str += f[i];
	}
	va_end(ap);
	return (str);
}

int					GString::FirstIndexOfChar(char c, G::IndexOption op) const
{
	if (op == G::INDEX_ALL_CHAR)
	{
		for (unsigned int i = 0; i < this->Length(); ++i)
		{
			if (this->_str[i] == c)
				return (i);
		}
	}
	else if (op == G::INDEX_THIS_CHAR)
	{
		for (unsigned int i = 0; i < this->Length(); ++i)
		{
			if (this->_str[i] != c)
				return (i);
		}
	}
	return (-1);
}

int					GString::FirstIndexOfChar(char c, char d, G::IndexOption op) const
{
	if (op == G::INDEX_ALL_CHAR)
	{
		for (unsigned int i = 0; i < this->Length(); ++i)
		{
			if (this->_str[i] >= c && this->_str[i] <= d)
				return (i);
		}
	}
	else if (op == G::INDEX_THIS_CHAR)
	{
		for (unsigned int i = 0; i < this->Length(); ++i)
		{
			if (this->_str[i] < c || this->_str[i] > d)
				return (i);
		}
	}
	return (-1);
}

int					GString::Find(const GString &f, CaseOption c) const
{
	if (f.Size() > this->_size)
		return (-1);
	int k = -1;
	for (unsigned int i = 0, j = 0; i < this->_size + 1; ++i)
	{
		if (f._str[j] == 0)
			return (k);
		GChar c1(this->_str[i]);
		GChar c2(f._str[j]);
		if (c == GString::CaseInsensitive)
		{
			c1 = c1.ToLower();
			c2 = c2.ToLower();
		}
		if (c1 == c2)
		{
			if (k == -1)
				k = i;
			j++;
		}
		else
		{
			k = -1;
			j = 0;
		}
	}
	return (-1);
}

int					GString::FirstIndexOf(const GString &d, CaseOption op) const
{
	return (this->Find(d, op));
}

int					GString::LastIndexOf(const GString &d, CaseOption op) const
{
	int pos = 0;
	int save = -1;
	while (true)
	{
		pos = this->Find(d, pos, op);
		if (pos == -1)
			return (save);
		save = pos;
		pos += d.Size();
	}
	return (-1);
}

int					GString::Find(const GString &f, unsigned int pos, CaseOption c) const
{
	if (f.Size() > this->_size)
		return (-1);
	int k = -1;
	for (unsigned int i = pos, j = 0; i < this->_size + 1; ++i)
	{
		if (f._str[j] == 0)
			return (k);
		GChar c1(this->_str[i]);
		GChar c2(f._str[j]);
		if (c == GString::CaseInsensitive)
		{
			c1 = c1.ToLower();
			c2 = c2.ToLower();
		}
		if (c1 == c2)
		{
			if (k == -1)
				k = i;
			j++;
		}
		else
		{
			return (this->Find(f, pos + 1, c));
		}
	}
	return (-1);
}

void				GString::Clear(void)
{
	if (this->_size > SIZE)
	{
		delete[] this->_str;
		this->_size = 0;
		this->_allocate = this->_size + SIZE;
		this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
	}
	this->_size = 0;
	this->_str[0] = 0;
}

void				GString::Truncate(unsigned int pos)
{
	if (pos > this->_size)
		return ;
	for (unsigned int i = pos; i < this->_size; ++i)
		this->_str[i] = 0;
}

bool				GString::IsNumeric(void) const
{
	for (unsigned int i = 0; i < this->_size; ++i)
	{
		if ((this->_str[i] < '0' || this->_str[i] > '9') || this->_str[i] == '.' || this->_str[i] == ',')
			return (false);
	}
	return (true);
}

bool				GString::IsAlpha(void) const
{
	for (unsigned int i = 0; i < this->_size; ++i)
	{
		if (this->_str[i] < 'a' || this->_str[i] > 'z')
			return (false);
		if (this->_str[i] < 'A' || this->_str[i] > 'Z')
			return (false);
	}
	return (true);
}

bool				GString::IsEmpty(void) const
{
	if (this->_size)
		return (false);
	return (true);
}

bool				GString::Contain(const GString &Str, CaseOption op) const
{
	if (this->Find(Str, op) != -1)
		return (true);
	return (false);
}

bool				GString::StartWith(const GString &str) const
{
	
	if (str.Length() > this->Length())
		return (false);
	for (unsigned int i = 0; i < str.Size(); ++i)
	{
		if (this->_str[i] != str._str[i])
			return (false);
	}
	return (true);
}

bool				GString::EndWith(const GString &str) const
{
	int size1 = this->Length() - 1;
	int size2 = str.Length() - 1;
	if (size2 > size1)
		return (false);
	for (unsigned int i = 0; i < str.Size(); ++i)
	{
		if (this->_str[size1 - i] != str._str[size2 - i])
			return (false);
	}
	return (true);
}

bool				GString::Compare(const GString &s) const
{
	if (s.Size() != this->Size())
		return (false);
	for (unsigned int i = 0; i < this->Size(); ++i)
	{
		if (this->_str[i] != s._str[i])
			return (false);
	}
	return (true);
}

GStringList			GString::Split(const GString &f, G::SplitOption splitop , CaseOption caseop) const
{
	GStringList	vect;
	if (this->Find(f, caseop) == -1)
	{
		vect.PushBack(*(new GString(GString::GetContent(this->_str, this->_size))));
		return (vect);
	}
	int pos = 0, pos1 = 0, pos2 = 0;
	while (true)
	{
		pos1 = pos;
		pos = this->Find(f, pos, caseop);
		if (pos == -1)
			break;
		pos2 = pos;
		GString ne(this->Substr(pos1, pos2));
		if ((splitop == G::SKIP_EMPTY_PARTS && ne.Size() != 0) || splitop == G::KEEP_EMPTY_PARTS) 
			vect.PushBack(*(new GString(ne)));
		pos += f.Size();
	}
	if (pos1 != 0)
	{
		GString ne(this->Substr(pos1, this->Size()));
		if ((splitop == G::SKIP_EMPTY_PARTS && ne.Size() != 0) || splitop == G::KEEP_EMPTY_PARTS) 
				vect.PushBack(*(new GString(ne)));
	}
	return (vect);	
}

GStringList			GString::Explode(const GString &f, G::SplitOption splitop , CaseOption caseop) const
{
	return (this->Split(f, splitop, caseop));
}

GString				GString::Fill(char c) const
{
	GString			to;
	delete[]		to._str;
	to._size = this->_size;
	to._allocate = to._size + SIZE;
	to._str = new char[((to._allocate + 1) % 8 == 0) ? to._allocate + 2 : to._allocate + 1];
	for (unsigned int i = 0; i < to._size; ++i)
		to._str[i] = c;
	to._str[to._size] = 0;
	return (to);
}

GString				GString::Fill(char c, unsigned int n) const
{
	GString			to;
	delete[]		to._str;
	to._size = this->_size;
	to._allocate = to._size + SIZE;
	to._str = new char[((to._allocate + 1) % 8 == 0) ? to._allocate + 2 : to._allocate + 1];
	for (unsigned int i = 0; i < to._size; ++i)
	{
		if (i < n)
			to._str[i] = c;
		else
			to._str[i] = this->_str[i];
	}
	to._str[to._size] = 0;
	return (to);
} 

GString				GString::ToUpper(void) const
{
	GString			to;
	delete[]		to._str;
	to._size = this->_size;
	to._allocate = to._size + SIZE;
	to._str = new char[((to._allocate + 1) % 8 == 0) ? to._allocate + 2 : to._allocate + 1];
	for (unsigned int i = 0; i < to._size; ++i)
	{
		if (this->_str[i] >= 'a' && this->_str[i] <= 'z')
			to._str[i] = this->_str[i] - 32;
		else
			to._str[i] = this->_str[i];
	}
	to._str[to._size] = 0;
	return (to);
}

GString				GString::ToLower(void) const
{
	GString			to;
	delete[]		to._str;
	to._size = this->_size;
	to._allocate = to._size + SIZE;
	to._str = new char[((to._allocate + 1) % 8 == 0) ? to._allocate + 2 : to._allocate + 1];
	for (unsigned int i = 0; i < to._size; ++i)
	{
		if (this->_str[i] >= 'A' && this->_str[i] <= 'Z')
			to._str[i] = this->_str[i] + 32;
		else
			to._str[i] = this->_str[i];
	}
	to._str[to._size] = 0;
	return (to);
}

GString				GString::Substr(unsigned int d, unsigned int f) const
{
	if (d == f)
		return ("");
	if (f > this->_size || d > this->_size || d >= f)
		return (GString::GetBuffer(this->_str, this->_size));
	GString			to;
	delete[]		to._str;
	to._size = f - d;
	to._allocate = to._size + SIZE;
	to._str = new char[((to._allocate + 1) % 8 == 0) ? to._allocate + 2 : to._allocate + 1];
	for (unsigned int i = d, j = 0; i < f; ++i)
		to._str[j++] = this->_str[i];
	to._str[f - d] = 0;
	return (to);
}

GString				GString::Substr(unsigned int d) const
{
	if (d > this->_size)
		return (GString::GetBuffer(this->_str, this->_size));
	GString			to;
	delete[]		to._str;
	to._size = this->_size - d;
	to._allocate = to._size + SIZE;
	to._str = new char[((to._allocate + 1) % 8 == 0) ? to._allocate + 2 : to._allocate + 1];
	for (unsigned int i = d, j = 0; i < this->_size; ++i)
		to._str[j++] = this->_str[i];
	to._str[this->_size - d] = 0;
	return (to);
}

GString				GString::Implode(GStringList &list, const GString &sep, G::SplitOption op)
{
	GString n;
	for (unsigned int i = 0; i < list.Size(); ++i)
	{
		if (op == G::SKIP_EMPTY_PARTS && list[i].Size() == 0)
			continue;
		if (i != 0)
			n += sep;
		n += list[i];
	}
	return (n);
}

GString				GString::Join(GStringList &list, const GString &sep, G::SplitOption op)
{
	return (GString::Implode(list, sep, op));
}

GString				GString::Implode(GStringList &list, G::SplitOption op)
{
	GString n;
	for (unsigned int i = 0; i < list.Size(); ++i)
	{
		if (op == G::SKIP_EMPTY_PARTS && list[i].Size() == 0)
			continue;
		n += list[i];
	}
	return (n);
}

GString				GString::Join(GStringList &list, G::SplitOption op)
{
	return (GString::Implode(list, op));
}

GString				GString::Remove(unsigned int pos, unsigned int nb) const
{
	if (pos + nb > this->_size)
		return (GString::GetBuffer(this->_str, this->_size));
	GString			to;
	delete[]		to._str;
	to._size = this->_size - nb;
	to._allocate = to._size + SIZE;
	to._str = new char[((to._allocate + 1) % 8 == 0) ? to._allocate + 2 : to._allocate + 1];
	for (unsigned int i = 0, j = 0; i < this->_size; ++i)
		if (i < pos || i >= pos + nb)
			to._str[j++] = this->_str[i];
	to._str[this->_size - nb] = 0;
	return (to);
}

GString				GString::Remove(const GString &g, CaseOption c) const
{
	int pos = this->Find(g, c);
	if (pos == -1)
		return (GString::GetBuffer(this->_str, this->_size));
	return (this->Remove(pos, g.Size()));
}

GString				GString::RightJustified(unsigned int nbr, char c) const
{
	if (nbr <= this->_size)
		return (GString::GetBuffer(this->_str, this->_size));
	GString			to;
	delete[]		to._str;
	to._size = nbr;
	to._allocate = to._size + SIZE;
	to._str = new char[((to._allocate + 1) % 8 == 0) ? to._allocate + 2 : to._allocate + 1];
	for (unsigned int i = 0, j = 0; i < nbr; ++i)
	{
		if (i < nbr - this->_size)
			to._str[i] = c;
		else
			to._str[i] = this->_str[j++];
	}
	to._str[nbr] = 0;
	return (to);
}

GString				GString::LeftJustified(unsigned int nbr, char c) const
{
	if (nbr <= this->_size)
		return (GString::GetBuffer(this->_str, this->_size));
	GString			to;
	delete[]		to._str;
	to._size = nbr;
	to._allocate = to._size + SIZE;
	to._str = new char[((to._allocate + 1) % 8 == 0) ? to._allocate + 2 : to._allocate + 1];
	for (unsigned int i = 0; i < nbr; ++i)
	{
		if (i < this->_size)
			to._str[i] = this->_str[i];
		else
			to._str[i] = c;
	}
	to._str[nbr] = 0;
	return (to);
}

GString				GString::Insert(unsigned int pos, const GString &c) const
{
	if (pos > this->_size)
		return (GString::GetBuffer(this->_str, this->_size));
	GString			to;
	delete[]		to._str;
	to._size = this->_size + c.Size();
	to._allocate = to._size + SIZE;
	to._str = new char[((to._allocate + 1) % 8 == 0) ? to._allocate + 2 : to._allocate + 1];
	for (unsigned int i = 0, j = 0; i < this->_size + 1; ++i)
	{
		if (pos == i)
		{
			for (; j < c.Size(); ++j)
				to._str[i + j] = c._str[j];
			to._str[i + j] = this->_str[i];
		}
		else
			to._str[i + j] = this->_str[i];
	}
	return (to);
}

GString				GString::Replace(const GString &f, const GString &r, CaseOption op) const
{
	GString g(this->_str);
	int pos = 1;
	while (pos != -1)
	{
		pos = g.Find(f, op);
		if (pos == -1)
			break;
		g = g.Remove(pos, f.Size());
		g = g.Insert(pos, r);
	}
	return (g);
}

GString				GString::GetLeftString(const GString &Start, CaseOption Case) const
{
	int p1 = this->Find(Start, Case);
	if (p1 == -1 || p1 == 0)
		return (GString::GetContent(this->_str, this->_size));
	return (this->Substr(0, p1));
}

GString				GString::GetRightString(const GString &Start, CaseOption Case) const
{
	int p1 = this->Find(Start, Case);
	p1 += Start.Size();
	if (p1 == -1 || (unsigned int)p1 == this->_size - 1)
		return (GString::GetContent(this->_str, this->_size));
	return (this->Substr(p1, this->Size()));
}

GString				GString::GetMiddleString(const GString &Start, const GString &End, CaseOption Case) const
{
	int p1 = this->Find(Start, Case);
	p1 += Start.Size();
	int p2 = this->Find(End, Case);
	if (p1 == -1 || p2 == -1 || p1 >= p2)
		return (GString::GetContent(this->_str, this->_size));
	return (this->Substr(p1, p2));
}

GString				GString::Reverse(void) const
{
	GString			to;
	delete[]		to._str;
	to._size = this->_size;
	to._allocate = to._size + SIZE;
	to._str = new char[((to._allocate + 1) % 8 == 0) ? to._allocate + 2 : to._allocate + 1];
	unsigned int i = 0;
	for (; i < this->_size; ++i)
		to._str[i] = this->_str[this->_size - i - 1];
	to._str[i] = 0;
	return (to);
}

GString				GString::LeftTrim(G::TrimOption op) const
{
	int indexEnd = 0;
	if (op == G::TRIM_BLANK)
	{
		for (unsigned int i = 0; i < this->_size; ++i)
		{
			if (this->_str[i] != '\n' && this->_str[i] != '\r' && this->_str[i] != '\t' && this->_str[i] != ' ')
			{
				indexEnd = i;
				break;
			}
		}
	}
	else if (op == G::TRIM_SPACE)
		indexEnd = this->FirstIndexOfChar(' ', G::INDEX_THIS_CHAR);
	else if (op == G::TRIM_TAB)
		indexEnd = this->FirstIndexOfChar('\t', G::INDEX_THIS_CHAR);
	else if (op == G::TRIM_ENTER)
		indexEnd = this->FirstIndexOfChar('\n', G::INDEX_THIS_CHAR);
	else if (op == G::TRIM_NUMBER)
		indexEnd = this->FirstIndexOfChar('0', '9', G::INDEX_THIS_CHAR);
	else if (op == G::TRIM_ALPHA)
	{
		for (unsigned int i = 0; i < this->_size; ++i)
		{
			if (this->_str[i] < 'A' || (this->_str[i] > 'Z' && this->_str[i] < 'a') || this->_str[i] > 'z')
			{
				indexEnd = i;
				break;
			}
		}
	}
	else if (op == G::TRIM_ALPHANUM)
	{
		for (unsigned int i = 0; i < this->_size; ++i)
		{
			if (this->_str[i] < '0' || (this->_str[i] > '9' && this->_str[i] < 'A') || (this->_str[i] > 'Z' && this->_str[i] < 'a') || this->_str[i] > 'z')
			{
				indexEnd = i;
				break;
			}
		}
	}
	return (this->Substr(indexEnd, this->Size()));
}

GString				GString::RightTrim(G::TrimOption op) const
{
	int indexEnd = 0;
	if (op == G::TRIM_BLANK)
	{
		for (int i = this->_size - 1; i > 0; --i)
		{
			if (this->_str[i] != '\n' && this->_str[i] != '\r' && this->_str[i] != '\t' && this->_str[i] != ' ')
			{
				indexEnd = i + 1;
				break;
			}
		}
	}
	else if (op == G::TRIM_SPACE)
		indexEnd = this->LastIndexOfChar(' ', G::INDEX_THIS_CHAR);
	else if (op == G::TRIM_TAB)
		indexEnd = this->LastIndexOfChar('\t', G::INDEX_THIS_CHAR);
	else if (op == G::TRIM_ENTER)
		indexEnd = this->LastIndexOfChar('\n', G::INDEX_THIS_CHAR);
	else if (op == G::TRIM_NUMBER)
		indexEnd = this->LastIndexOfChar('0', '9', G::INDEX_THIS_CHAR);
	else if (op == G::TRIM_ALPHA)
	{
		for (int i = this->_size - 1; i > 0; --i)
		{
			if (this->_str[i] < 'A' || (this->_str[i] > 'Z' && this->_str[i] < 'a') || this->_str[i] > 'z')
			{
				indexEnd = i + 1;
				break;
			}
		}
	}
	else if (op == G::TRIM_ALPHANUM)
	{
		for (int i = this->_size -1; i > 0; --i)
		{
			if (this->_str[i] < '0' || (this->_str[i] > '9' && this->_str[i] < 'A') || (this->_str[i] > 'Z' && this->_str[i] < 'a') || this->_str[i] > 'z')
			{
				 indexEnd = i + 1;
				break;
			}
		}
	}
	return (this->Substr(0, indexEnd));
}

GString				GString::Trim(G::TrimOption op) const
{
	GString g;
	g = this->RightTrim(op);
	g = g.LeftTrim(op);
	return (g);
}
// CONVERSION
	
#if defined (WIN32) | defined (_WIN32) | defined (__WIN32) | defined (WIN64) | defined (__WIN64)
std::wstring		GString::ToWString(void) const
{
	unsigned int size = this->_size;
	wchar_t	*ws = new wchar_t[size + 1];
	for (unsigned int i = 0; i < size + 1; i++)
		ws[i] = this->_str[i];
	std::wstring s(ws);
	delete[] ws;
	return (s);
}

CString				GString::ToCString(void) const
{
	CString s(this->_str);
	return (s);
}

wchar_t				*GString::ToWChar_t(void) const
{
	unsigned int size = this->_size;
	wchar_t	*ws = new wchar_t[size + 1];
	for (unsigned int i = 0; i < size + 1; i++)
		ws[i] = this->_str[i];
	return (ws);
}

LPCSTR				GString::ToLPCSTR(void) const
{
	LPCSTR test = this->_str;
	return (test);
}

#endif

bool				GString::ToBool(void) const
{
	GString f("false");
	if (f == GString(this->_str))
		return (false);
	GString t("true");
	if (t == GString(this->_str))
		return (true);
	throw GException(G::NOT_A_BOOLEEN);
}

std::string			GString::ToStdString(void) const
{
	std::string s(this->_str);
	return (s);
}

char				*GString::ToChar(void) const
{
	char *newStr = new char[this->Size() + 1];
	for (unsigned int i = 0; i < this->Size() + 1; ++i)
		newStr[i] = this->_str[i];
	return (newStr);
}

int					GString::ToInt(void) const
{
	int nbr = 0;
	int mult = 1;
	for (int i = this->_size - 1; i >= 0; --i)
	{
		if (i == 0 && this->_str[i] == '-')
		{
			nbr *= -1;
			break;
		}
		else if (this->_str[i] >= '0' && this->_str[i] <= '9')
		{
			nbr += mult * (this->_str[i] - '0');
			mult *= 10;
		}
		else if (this->_str[i] != '+')
		{
			GWarning::Warning("Warning - class GString - method ToInt(void) const \t\t=> Allowed char are '0-9', '+' and '-' !");
			throw GException(G::NOT_AN_INTEGER);
		}
	}
	return (nbr);
}

double				GString::ToDouble(void) const
{
	int pos = this->Find(".");
	if (pos == -1)
		return (0);
	int nbr = 0;
	int mult = 1;
	for (int i = pos - 1; i >= 0; --i)
	{
		if (i == 0 && this->_str[i] == '-')
		{
			nbr *= -1;
			break;
		}
		else if (this->_str[i] >= '0' && this->_str[i] <= '9')
		{
			nbr += mult * (this->_str[i] - '0');
			mult *= 10;
		}
		else if (this->_str[i] != '+')
		{
			GWarning::Warning("Warning - class GString - method ToInt(void) const \t\t=> Allowed char are '0-9', '+' and '-' !");
			throw GException(G::NOT_AN_INTEGER);
		}
	}
	return (nbr);
	return (nbr);
}
// SURCHARGES OPERATEURS

std::ostream		&operator<<(std::ostream &out, const GString &s)
{
	out << s._str;
	return (out);
}

std::ostream		&operator<<(std::ostream &out, const GString *s)
{
	out << s->_str;
	return (out);
}

char				GString::operator[](unsigned int j) const
{
	if (j < this->_size)
		return (this->_str[j]);
	return (' ');
}

bool				GString::operator==(const GString &s) const
{
	return (this->Compare(s));
}

bool				GString::operator!=(const GString &s) const
{
	return (!this->Compare(s));
}

bool				GString::operator>(const GString &s) const
{
	for (unsigned int i = 0; i < this->_size + 1; ++i)
	{
		if (this->_str[i] > s._str[i])
			return (true);
		if (this->_str[i] < s._str[i])
			return (false);
	}
	return (false);
}

bool				GString::operator<(const GString &s) const
{
	for (unsigned int i = 0; i < this->_size + 1; ++i)
	{
		if (this->_str[i] < s._str[i])
			return (true);
		if (this->_str[i] > s._str[i])
			return (false);
	}
	return (false);
}

GString				&GString::operator=(const GString &s)
{
	this->_size = s.Size();
	if (this->_allocate < s.Size())
	{
		delete[] this->_str;
		this->_allocate = this->_size + SIZE;
		this->_str = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
	}
	for (unsigned int i = 0; i < this->_size + 1; ++i)
		this->_str[i] = s._str[i];
	for (unsigned int i = this->_size + 1; i < this->_allocate ; i++)
		this->_str[i] = 0;
	return (*this);
}

GString				&GString::operator+=(const GString &s)
{
	if (this->_allocate < this->_size + s.Size() || this->_size + s.Size() < this->_allocate - SIZE * 2)
	{
		this->_allocate = this->_size + s._size + SIZE;
		char *newStr = new char[((this->_allocate + 1) % 8 == 0) ? this->_allocate + 2 : this->_allocate + 1];
		unsigned int i = 0;
		for (; i < this->_size; ++i)
			newStr[i] = this->_str[i];
		for (unsigned int j = 0; j < s.Size(); ++j, ++i)
			newStr[i] = s._str[j];
		newStr[i] = 0;
		this->_size = i;
		delete[] this->_str;
		this->_str = newStr;
	}
	else
	{
		unsigned int i = this->_size;
		for (unsigned int j = 0; j < s.Size(); ++j, ++i)
			this->_str[i] = s._str[j];
		this->_str[i] = 0;
		this->_size = this->_size + s.Size();
	}
	return (*this);
}

GString				operator+(const char *str, const GString &g)
{
	
	GString			s(str);
	GString			to;
	delete[]		to._str;
	to._size = g.Size() + s.Size();
	to._allocate = to._size + SIZE;
	to._str = new char[((to._allocate + 1) % 8 == 0) ? to._allocate + 2 : to._allocate + 1];
	unsigned int	i = 0;
	for (; i < s.Size(); ++i)
		to._str[i] = s._str[i];
	for (unsigned int j = 0; j < g.Size(); ++j, ++i)
		to._str[i] = g._str[j];
	to._str[i] = 0;
	return (to);
}

GString				operator+(const GString &g, const char *str)
{
	
	GString			s(str);
	GString			to;
	delete[]		to._str;
	to._size = g.Size() + s.Size();
	to._allocate = to._size + SIZE;
	to._str = new char[((to._allocate + 1) % 8 == 0) ? to._allocate + 2 : to._allocate + 1];
	unsigned int	i = 0;
	for (; i < g.Size(); ++i)
		to._str[i] = g._str[i];
	for (unsigned int j = 0; j < s.Size(); ++j, ++i)
		to._str[i] = s._str[j];
	to._str[i] = 0;
	return (to);
}

GString				operator+(const GString &g, const GString &s)
{
	
	GString			to;
	delete[]		to._str;
	to._size = g.Size() + s.Size();
	to._allocate = to._size + SIZE;
	to._str = new char[((to._allocate + 1) % 8 == 0) ? to._allocate + 2 : to._allocate + 1];
	unsigned int	i = 0;
	for (; i < g.Size(); ++i)
		to._str[i] = g._str[i];
	for (unsigned int j = 0; j < s.Size(); ++j, ++i)
		to._str[i] = s._str[j];
	to._str[i] = 0;
	return (to);
}

std::istream		&operator>>(std::istream &in, GString &s)
{
	char ch = 0;
	in.get(ch);
	while (in)
	{
		if (ch == '\n')
			return (in);
		s += ch;
		in.get(ch);
	}
	return (in);
}
