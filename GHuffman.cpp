
#include "GHuffman.h"
#include "GFileInfos.h"
#include "GFile.h"
#include "GExecutionTime.h"

GSheet::GSheet(void) : _weight(0), _data(0), _left(NULL), _right(NULL)
{
	this->_node = true;
}

GSheet::GSheet(long long weight, unsigned char data) : _weight(weight), _left(NULL), _right(NULL)
{
	this->_data = data;
	this->_node = false;
}

GSheet::GSheet(GSheet *left, GSheet *right) : _weight(0), _data(0)
{
	this->_left = left;
	this->_right = right;
	this->_node = true;
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
	this->_left = s._left;
	this->_right = s._right;
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

void			GSheet::SetLeft(GSheet *left)
{
	if (this->_left)
		delete this->_left;
	this->_left = left;
}

void			GSheet::SetRight(GSheet *right)
{
	if (this->_right)
		delete this->_right;
	this->_right = right;
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

bool			GHuffman::Compress(const GString &FileIn, const GString &FileOut)
{
	GFileInfos	f(FileIn);
	if (!f.Exist())
		return (false);
	GVector<GSheet*>	_treeV;
	GSheet				*_tree;
	GString				_content;
	unsigned int		_nbChar = 0;
	GFile	fileIn(FileIn);
	fileIn.Open(true);
	GHuffmanStats *_stats = new GHuffmanStats[256];
	_content = fileIn.Read();
	fileIn.Close();
	for (unsigned int i = 0; i < _content.Size(); i++)
	{
		if (_stats[(unsigned char)_content[i]]._frequence == 0)
			_nbChar++;
		_stats[(unsigned char)_content[i]]._frequence++;
	}
	for (unsigned int i = 0; i < 256; i++)
		if (_stats[i]._frequence)
		{
			unsigned int	pos = _treeV.Size();
			for (unsigned int j = 0; j < pos; j++)
				if (_stats[i]._frequence <= _treeV[j]->GetWeight())
					pos = j;
			_treeV.Insert(pos, new GSheet(_stats[i]._frequence, i));
		}
	if (_treeV.IsEmpty())
		return (false);
	while (_treeV.Size() > 1)
	{
		GSheet	*top1(_treeV.PopFront());
		GSheet	*top2(_treeV.PopFront());
		GSheet	*fusion = new GSheet(top1, top2);
		unsigned int	pos = _treeV.Size();
		for (unsigned int i = 0; i < pos; i++)
			if (fusion->GetWeight() <= _treeV[i]->GetWeight())
				pos = i;
		_treeV.Insert(pos, fusion);
	}
	_tree = _treeV.PopFront();
	Calculate(_stats, _tree, 0, -1);
	GFile	file(FileOut);
	file.Open(true);
	file.Clear();
	GHuffmanHeader	Header;
	Header._nbChar = _nbChar;
	Header._size = (long)f.Size();
	int	pos = FileIn.LastIndexOf(".");
	if (pos == GString::NotFound)
		for (unsigned int i = 0; i < 4; ++i)
			Header._extension[i] = 0;
	else
	{
		int	dif = FileIn.Size() - pos;
		if (dif == 0)
			for (unsigned int i = 0; i < 4; ++i)
				Header._extension[i] = 0;
		else
		{
			pos++;
			unsigned int i = 0;
			for (; i < 4 && pos < (int)FileIn.Size(); i++)
				Header._extension[i] = FileIn[pos++];
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
		if (_stats[i]._frequence)
		{
			file.Write(&_stats[i]._nbits, sizeuc);
			if (_stats[i]._nbits < (sizeus << 3))
				file.Write(&_stats[i]._code, sizeus);
			else
				file.Write(&_stats[i]._code, sizeui);
			file.Write(&i, sizeuc);
		}
	}
	unsigned int	j = 0;
	unsigned int	i = 1;
	long			compteur = 1;
	long			taille = _content.Size();
	int				temp = 0;
	unsigned char	c;
	while (compteur < taille + 1) 
	{
		c = _content[compteur - 1];
		temp += ((_stats[c]._code) >> (_stats[c]._nbits - 1 - j)) & 1;
		if (i >= sizeex && j >= (_stats[c]._nbits - 1))
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
		else if (j >= (_stats[c]._nbits - 1))
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
	delete[] _stats;
	return (true);
}

void			Calculate(GHuffmanStats *_stats, GSheet *a, int code, int n)
{
	if (a && _stats)
	{
		if (!a->IsNode())
		{
			_stats[a->GetData()]._code = code;
			_stats[a->GetData()]._nbits = n + 1;
		}
		else
		{
			if (a->GetLeft())
				Calculate(_stats, a->GetLeft(), code << 1, n + 1);
			if (a->GetRight())
				Calculate(_stats, a->GetRight(), (code << 1) + 1, n + 1);
		}
	}
}

bool			GHuffman::Decompress(const GString &FileIn, const GString &FileOut)
{
	GFileInfos	f(FileIn);
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
		GFile			out(FileOut);
		out.Clear();
		out.Open(true);
		GFile			file(FileIn);
		file.Open(true);
		file.Read(&Header, sizeof(Header));
		unsigned int i = 0;
		GExecutionTime	time;
		GExecutionTime	t2;
		for (; i < Header._nbChar; i++)
		{
			code = 0;
			file.Read(&codeencours, sizeuc);
			(codeencours < (sizeuc << 3)) ? file.Read(&code, sizeus) : file.Read(&code, sizeui);
			file.Read(&carac, sizeuc);
			BuildTree(r, codeencours, code, carac);
			std::cerr << "Sheet Added : " << t2.Restart() << std::endl;
		}
		std::cerr << "TreeBuilded : " << time.Restart() << std::endl;
		i = 0;
		unsigned int j = 0;
		file.Read(&codeencours, sizeuc);	
		while (k < Header._size + 1)
		{
			recherche = Find(code, j, r, &carac);
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

void			BuildTree(GSheet *r, int nb, int code, unsigned char c)
{
	if (nb == 1)
	{
		if (!(code & 1))
			r->SetLeft(new GSheet(0, c));
		else
			r->SetRight(new GSheet(0, c));
	}
	else if (!((code >> (nb - 1)) & 1))
	{
		if (r->GetLeft() == NULL)
			r->SetLeft(new GSheet);
		BuildTree(r->GetLeft(), nb - 1, code, c);
	}
	else
	{
		if (r->GetRight() == NULL)
			r->SetRight(new GSheet);
		BuildTree(r->GetRight(), nb - 1, code, c);
	}
}

bool			Find(unsigned int code, unsigned int nb, GSheet *r, unsigned char* cPtr)
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
				return (Find(code, nb - 1, r->GetLeft(), cPtr));
			else
				return (false);
		}
		else
		{
			if (r->GetRight())
				return (Find(code, nb - 1, r->GetRight(), cPtr));
			else
				return (false);
		}
	}
	return (false);
}
