
#include "GHuffman.h"
#include "GFileInfos.h"
#include "GFile.h"
#include "GStr.h"

GSheet::GSheet(void) : _weight(0), _data(0), _left(NULL), _right(NULL)
{
	this->_node = true;
}

GSheet::GSheet(GSheet *s)
{
	if (s)
	{
		this->_node = s->_node;
		this->_data = s->_data;
		this->_weight = s->_weight;
		this->_left = new GSheet(s->_left);
		this->_right = new GSheet(s->_right);
	}
	else
	{
		this->_node = false;
		this->_data = NULL;
		this->_weight = NULL;
		this->_left = NULL;
		this->_right = NULL;
	}
}

GSheet::GSheet(long long weight, unsigned char data) : _weight(weight), _data(data), _left(NULL), _right(NULL)
{
	this->_node = false;
}

GSheet::GSheet(const GSheet &s)
{
	this->_node = s._node;
	this->_data = s._data;
	this->_weight = s._weight;
	this->_left = new GSheet(s._left);
	this->_right = new GSheet(s._right);
}

GSheet::GSheet(GSheet *left, GSheet *right) : _weight(0), _data(0)
{
	this->_left = new GSheet(left);
	this->_right = new GSheet(right);
	this->_node = true;
	if (this->_left)
		this->_weight += this->_left->GetWeight();
	if (this->_right)
		this->_weight += this->_right->GetWeight();
}

GSheet::GSheet(const GSheet &left, const GSheet &right) : _weight(0), _data(0)
{
	this->_node = true;
	this->_left = new GSheet(left);
	this->_right = new GSheet(right);
	if (this->_left)
		this->_weight += this->_left->GetWeight();
	if (this->_right)
		this->_weight += this->_right->GetWeight();
}

GSheet::~GSheet(void)
{
	if (this->_left)
		delete this->_left;
	if (this->_right)
		delete this->_right;
}

bool			GSheet::operator<=(const GSheet &s) const
{
	return (this->_weight <= s._weight);
}

GSheet			&GSheet::operator=(const GSheet &s)
{
	this->_data = s._data;
	this->_weight = s._weight;
	this->_left = new GSheet(s._left);
	this->_right = new GSheet(s._right);
	this->_node = this->_node;
	return (*this);
}

long long		GSheet::GetWeight(void) const
{
	return (this->_weight);
}

unsigned char	GSheet::GetData(void) const
{
	return (this->_data);
}

bool			GSheet::IsNode(void) const
{
	return (this->_node);
}

GSheet			*GSheet::GetLeft(void)
{
	return (this->_left);
}

GSheet			*GSheet::GetRight(void)
{
	return (this->_right);
}

void			GSheet::SetRight(unsigned char c, bool node)
{
	std::cerr << "Set Right  : " << c << " " << node << std::endl;
	if (this->_right)
		delete this->_right;
	this->_right = new GSheet(0, c);
	this->_node = node;
}

void			GSheet::SetLeft(unsigned char c, bool node)
{
	std::cerr << "Set Left  : " << c << " " << node << std::endl;
	if (this->_left)
		delete this->_left;
	this->_left = new GSheet(0, c);
	this->_node = node;
}

std::ostream&	operator<<(std::ostream &os, GSheet *s)
{
	if (s)
	{
		if (s->_node)
			os << "Node :   ";
		else
			os << "Data : " << s->_data << " ";
		os << s->_weight;
		if (s->_node)
		{
			os << std::endl;
			os << "Left  : " << s->_left;
			os << std::endl;
			os << "Right : " << s->_right;
		}
	}
	else
		os << "GSheet NULL";
	return (os);
}

std::ostream&	operator<<(std::ostream &os, const GSheet &s)
{
	if (s._node)
		os << "Node :   ";
	else
		os << "Data : " << s._data << " ";
	os << s._weight;
	if (s._node)
	{
		os << std::endl;
		os << "   Left  : " << s._left;
		os << std::endl;
		os << "   Right : " << s._right;
	}
	return (os);
}

GHuffman::GHuffman(const GString &file) : _file(file), _stats(NULL), _nbChar(0), _tree(NULL)
{
}

GHuffman::~GHuffman(void)
{
	if (this->_stats)
		delete this->_stats;
	if (this->_tree)
		delete this->_tree;
}

bool			GHuffman::CreateStats(void)
{
	GFileInfos	f(this->_file);
	if (f.Exist() && !this->_stats)
	{
		GFile	file(this->_file);
		file.Open(true);
		this->_stats = new GHuffmanStats[256];
		this->_content = file.Read();
		for (unsigned int i = 0; i < this->_content.Size(); i++)
		{
			if (this->_stats[(unsigned char)this->_content[i]]._frequence == 0)
				this->_nbChar++;
			this->_stats[(unsigned char)this->_content[i]]._frequence++;
		}
		
		file.Close();
		return (true);
	}
	return (false);
}

bool			GHuffman::CreateTree(void)
{
	this->CreateStats();
	if (this->_stats && this->_treeV.IsEmpty())
	{
		for (unsigned int i = 0; i < 256; i++)
			if (this->_stats[i]._frequence)
				this->_treeV.PushSorted(GSheet(this->_stats[i]._frequence, i));
		if (this->_treeV.IsEmpty())
			return (false);
		while (this->_treeV.Size() != 1)
		{
			GSheet	top1(this->_treeV.PopFront());
			GSheet	top2(this->_treeV.PopFront());
			GSheet	fusion(GSheet(top1, top2));
			this->_treeV.PushSorted(fusion);
		}
		this->_tree = new GSheet(this->_treeV.Front());
		this->Calculate(this->_tree, 0, -1);
		return (true);
	}
	return (false);
}

bool			GHuffman::Compress(const GString &File)
{
	if (this->_stats && !this->_treeV.IsEmpty())
	{
		GFile	file(File);
		file.Open(true);
		file.Clear();
		GFileInfos		f(this->_file);
		GHuffmanHeader	Header;
		Header._nbChar = this->_nbChar;
		Header._size = (long)f.Size();
		int	pos = this->_file.LastIndexOf(".");
		if (pos == GString::NotFound)
			for (unsigned int i = 0; i < 4; ++i)
				Header._extension[i] = 0;
		else
		{
			int	dif = this->_file.Size() - pos;
			if (dif == 0)
				for (unsigned int i = i; i < 4; ++i)
					Header._extension[i] = 0;
			else
			{
				pos++;
				unsigned int i = 0;
				for (; i < 4 && pos < (int)this->_file.Size(); i++)
					Header._extension[i] = this->_file[pos++];
				for (; i < 4; i++)
					Header._extension[i] = 0;;
			}
		}
		file.Write(&Header, sizeof(Header));
		unsigned int	sizeus = sizeof(unsigned short);
		unsigned int	sizeuc = sizeof(unsigned char);
		unsigned int	sizeui = sizeof(unsigned int);
		unsigned int	sizeex = sizeuc << 3;
		for (unsigned int i = 0; i < 256; i++)
		{
			if (this->_stats[i]._frequence)
			{
				file.Write(&this->_stats[i]._nbits, sizeuc);
				if (this->_stats[i]._nbits < (sizeus << 3))
					file.Write(&this->_stats[i]._code, sizeus);
				else
					file.Write(&this->_stats[i]._code, sizeui);
				file.Write(&i, sizeuc);
			}
		}
		unsigned int	j = 0;
		unsigned int	i = 1;
		long			compteur = 1;
		long			taille = this->_content.Size();
		int				temp = 0;
		unsigned char	c;
		while (compteur < taille + 1) 
		{
			c = this->_content[compteur - 1];
			temp += ((this->_stats[c]._code) >> (this->_stats[c]._nbits - 1 - j)) & 1;
			if (i >= sizeex && j >= (this->_stats[c]._nbits - 1))
			{
				file.Write(&temp, sizeuc);
				temp = 0;
				i = 1;
				j = 0;
				compteur++;
			}
			else if (i >= sizeex)
			{
				file.Write(&temp, sizeuc);
				temp = 0;
				i = 1;
				j++;
			}
			else if (j >= (this->_stats[c]._nbits - 1))
			{
				temp = temp << 1;
				i++;
				compteur++;
				if (compteur == taille + 1)
					file.Write(&temp, sizeuc);
				j = 0;
			}
			else
			{
				temp = temp << 1;
				i++;
				j++;
			}
		}
		file.Close();
		return (true);
	}
	return (false);
}

void			GHuffman::Calculate(GSheet *a, int code, int n)
{
	if (a && this->_stats)
	{
		if (!a->IsNode())
		{
			this->_stats[a->GetData()]._code = (code = (code << 1) + a->IsNode());
			this->_stats[a->GetData()]._nbits = n + 1;
		}
		else
		{
			if (a->GetLeft())
				this->Calculate(a->GetLeft(), code, n + 1);
			if (a->GetRight())
				this->Calculate(a->GetRight(), code, n + 1);
		}
	}
}

bool			GHuffman::Decompress(const GString &File)
{
	GFileInfos	f(this->_file);
	if (f.Exist())
	{
		unsigned int	code = 0;
		unsigned char	carac;
		unsigned char	codeencours = 0;
		unsigned int	k = 1;
		GHuffmanHeader	Header;
		bool			recherche = false;

		unsigned int	sizeus = sizeof(unsigned short);
		unsigned int	sizeuc = sizeof(unsigned char);
		unsigned int	sizeui = sizeof(unsigned int);
		unsigned int	sizeex = sizeuc << 3;

		GSheet			*r = new GSheet;
		GFile			out(File);
		out.Clear();
		out.Open(true);
		GFile			file(this->_file);
		file.Open(true);
		file.Read(&Header, sizeof(Header));
		unsigned int i = 0;
		for (; i < Header._nbChar; i++)
		{
			code = 0;
			file.Read(&codeencours, sizeuc);
			(codeencours < (sizeuc << 3)) ? file.Read(&code, sizeus) : file.Read(&code, sizeui);
			file.Read(&carac, sizeuc);
			this->BuildTree(r, codeencours, code, carac);
		}
		std::cerr << r << std::endl;
		i = 0;
		unsigned int j = 0;
		file.Read(&codeencours, sizeuc);	
		while (k < Header._size + 1)
		{
			std::cerr << "Find" << std::endl;
			recherche = this->Find(code, j, r, &carac);
			std::cerr << "Finded : " << recherche << " " << carac << std::endl;
			if (i < sizeex && recherche == false)
			{
				code = code << 1;
				code += (codeencours >> (sizeex - i - 1)) & 1; // % 2
				i++;
				j++;
			}
			else if (recherche == true && i < sizeex)
			{
				code = 0;
				j = 1;
				code = (codeencours >> (sizeex - i - 1)) & 1; // % 2
				i++;
				k++;
				out.Write(&carac, sizeuc);
			}
			else if (recherche == false && i == sizeex)
			{
				i = 0;
				file.Read(&codeencours, sizeuc);
			}
			else
			{
				i = 0;
				j = 0;
				code = 0;
				k++;
				out.Write(&carac, sizeuc);
				file.Read(&codeencours, sizeuc);
			}
		}
		return (true);
	}
	return (false);
}

void			GHuffman::BuildTree(GSheet *r, int nb, int code, unsigned char c)
{
	if (nb == 1)
	{
		if (!(code & 1))
			r->SetLeft(c, false);
		else
			r->SetRight(c, true);
	}
	else if (!((code >> (nb - 1)) & 1))
	{
		if (r->GetLeft() == NULL)
			r->SetLeft('\0', false);
		this->BuildTree(r->GetLeft(), nb - 1, code, c);
	}
	else
	{
		if (r->GetRight() == NULL)
			r->SetRight('\0', true);
		this->BuildTree(r->GetRight(), nb - 1, code, c);
	}
}

bool			GHuffman::Find(unsigned int code, unsigned int nb, GSheet *r, unsigned char* cPtr)
{
	unsigned int temp;
	if (!nb && !r->IsNode())
	{
		*cPtr = r->GetData();
		return (true);
	}
	else
	{
		temp = code >> (nb - 1);
		if (!(temp & 1))
		{
			if (r->GetLeft())
				return (this->Find(code, nb - 1, r->GetLeft(), cPtr));
			else
				return (false);
		}
		else
		{
			if (r->GetRight())
				return (this->Find(code, nb - 1, r->GetRight(), cPtr));
			else
				return (false);
		}
	}
	return (false);
}
