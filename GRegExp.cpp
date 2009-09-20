#include "GRegExp.h"
#include "GException.h"

using namespace std;

GRegExp::GRegExp(GString preg, GString skip)
{
	_preg = preg;
	_opt = GVector<GRegExpOpt>();
	_skip = skip;
	_burn = GString(" \t\n\r");
}

GVector<GString> *GRegExp::pregMatch(GString &str)
{
	str = BurnCorner(str);
	GString t = this->skipDouble(str);
	GStringList s = _preg.Explode("(.*)", G::KEEP_EMPTY_PARTS);
	GVector<GString> r;
	for (unsigned int i = 0; i < s.Size(); i++)
	{
		if (this->isPos(s[i], "(.*)") > -1)
			r+=GString("");
		else
			r+=BurnCorner(GString(s[i]));
	}
	if (isNPos(_preg, "(.*)", _preg.Size() - 4) > 0)
	{
		r.Erase(r.Size() - 1);
	}
	GVector<GString> *res = new GVector<GString>;
	if (r.Size() < 1)
	{
		if (this->isContener(_preg, "(.*)"))
		{
			(*res)+= str;
			return res;
		}
		else
		{
			return NULL;
		}
	}
	unsigned int pos = 0;
	unsigned int reg = 0;
	if (!this->isContener(_preg, "(.*)"))
	{
		if (this->isContener(str,r[0]))
		{
			pos+=r[0].Size();
			r.Erase(0);
		}
		else
			return NULL;
	}
	else
	{
		if (r.Size() > 0 && r[r.Size() - 1].Size() == 0)
			r.Erase(r.Size() - 1);
	}
	for (; reg < r.Size(); reg++)
	{
		int restmp = longRes(&r, pos, reg, str);
		if (restmp < 0)
			return NULL;
		GString mot = "";
		for (unsigned int i = 0; i < (unsigned int)restmp; i++)
			mot += str[pos + i];
		(*res)+= BurnCorner(mot);
		pos += restmp + r[reg].Size();
	}
	if (reg == r.Size() && _preg.Size() > 4 && isNPos(_preg, "(.*)", _preg.Size() - 4) > 0)
	{
		int restmp;
		if (str.Size() == pos && (_opt.Size() == 0 || (_opt.Size() > reg && _opt[reg].getEmp() == EMPTY)))
			restmp = 0;
		else
			restmp = longRes(&r, pos, reg, str);
		if (restmp < 0)
			return NULL;
		if (pos + restmp > str.Size())
			throw GException("Error RegExp");
		GString mot = "";
		for (unsigned int i = 0; i < (unsigned int)restmp; i++)
			mot += str[pos + i];
		(*res)+= BurnCorner(mot);
		return res;
	}
	return res;
}

int GRegExp::isPos(GString str1, GString str2)
{
	if (str1.Size() < str2.Size())
		return -1;
	for (unsigned int i = 0; i <= str1.Size() - str2.Size(); i++)
	{
		unsigned int j = 0;
		while (str1[i + j] == str2[j] && j < str2.Size())
			j++;
		if (j == str2.Size())
			return i;
	}
	return -1;
}

int GRegExp::isNPos(GString str1, GString str2, unsigned int pos)
{
	if (str1.Size() + pos < str2.Size())
		return -1;
	for (unsigned int i = pos; i <= str1.Size() - str2.Size(); i++)
	{
		unsigned int j = 0;
		while (str1[i + j] == str2[j] && j < str2.Size())
			j++;
		if (j == str2.Size())
			return i;
	}
	return -1;
}


GRegExp::~GRegExp(void)
{

}

GString GRegExp::skipDouble(GString str)
{
	GString res("");
	for (unsigned int i = 0; i < str.Size() - 1; i++)
	{
		if (str[i] == str[i + 1])
		{
			unsigned int j = 0;
			while (j < _skip.Size() && _skip[j] != str[i])
				j++;
			if (j == _skip.Size())
				res += str[i];
		}
		else
			res += str[i];
	}
	res += str[str.Size() - 1];
	return res;
}

int GRegExp::longRes(GVector<GString> *res, unsigned int pos, unsigned int reg, GString &str)
{
	if ( pos > str.Size() || res->Size() < reg)
		return -1;
	if (!res || res->Size() == reg)
	{
		if (this->_opt.Size() == 0 || (this->_opt.Size() > reg && (_opt[reg].getObliWord().Size() == 0)))
		{
			if (_opt.Size() != 0)
			{
				GString tmp = _opt[reg].getStopChar();
				for (unsigned int i = pos; i < str.Size(); i++)
					for (unsigned int j = 0; j < tmp.Size(); j++)
						if (tmp[j] == str[i])
							return -1;
				if (_opt[reg].getEmp() == NOEMPTY && (str.Size() - pos) == 0)
					return -1;
				return str.Size() - pos;
			}
			return str.Size() - pos;
		}
		return str.Size();
	}
	if (this->_opt.Size() == 0 || (this->_opt.Size() > reg && (_opt[reg].getObliWord().Size() == 0)))
	{
		unsigned int i = pos;
		while (i < str.Size() - (*res)[reg].Size() + 1)
		{
			if (this->_opt.Size() > reg)
			{
				GString tmp = _opt[reg].getStopChar();
				for (unsigned int j = 0; j < tmp.Size(); j++)
				{
					if (tmp[j] == str[i])
					{
						if ((int)i - (int)pos < 0)
							return -1;
						else if (this->_opt.Size() == 0 || (this->_opt.Size() > reg && _opt[reg].getEmp() == EMPTY))
							return i - pos;
						else if (i - pos > 0)
							return i - pos;
						return -1;
					}
				}
			}
			if (_opt.Size() > reg + 1 && _opt[reg + 1].getStopChar() == "" && _opt[reg + 1].getObliWord().Size() == 0)
			{
				if (_opt[reg].getStopChar().Size() == 0 && _opt[reg].getObliWord().Size() == 0)
				{
					unsigned int j = 0;
					while ((*res)[reg].Size() > j && (*res)[reg][j] == str[i + j])
						j++;
					if (j == (*res)[reg].Size())
						return i - pos;
				}
				i++;
			}	
			else
			{
				unsigned int j = 0;
				if ((*res)[reg].Size() == 0)
				{
					if (this->_opt.Size() > reg && _opt[reg].getEmp() == NOEMPTY && (i - pos) > 0)
					{
						if (longRes(res, i, reg + 1, str) != -1)
							return i - pos;
					}
					else
					{
						if (this->_opt.Size() <= reg || (this->_opt.Size() > reg && _opt[reg].getEmp() == EMPTY))
							return i - pos;
					}
				}
				else
				{
					while ((*res)[reg].Size() > j && (*res)[reg][j] == str[i + j])
						j++;
				/* test fin avec (.*)t sans opt*/
					if (j == (*res)[reg].Size())
					{
						if (this->_opt.Size() > reg)
						{
							if ((_opt[reg].getEmp() == NOEMPTY && (i - pos) > 1) || _opt[reg].getEmp() == EMPTY)
								if ((reg + 1 < res->Size()) || (reg + 1 == res->Size() && str.Size() == i + (*res)[reg].Size()))
									return i - pos;
						}
						else
						{
							if ((reg + 1 < res->Size()) || (reg + 1 == res->Size() && str.Size() == i + (*res)[reg].Size()))
								return i - pos;
						}
					}
				}
				i++;
			}
		}
		return -1;
	}
	if (this->_opt.Size() > reg && _opt[reg].getObliWord().Size() > 0)
	{
		GVector<GString> tmp = _opt[reg].getObliWord();
		for (unsigned int i = 0; i < tmp.Size(); i++)
		{	
			if (tmp[i].Size() <= str.Size() + pos)
			{
				unsigned int j = 0;
				while (j < tmp[i].Size() && tmp[i][j] == str[pos + j])
					j++;
				if (j == tmp[i].Size())
				{
					if (reg == res->Size() && str.Size() == pos + j)
						return j;
					if (reg < res->Size())
					{
						unsigned int k = 0;
						while (k < str.Size() && k < (*res)[reg].Size() && str[k + pos + j] == (*res)[reg][k])
							k++;

						/*test fin de chaine */
						if ((*res)[reg].Size() == k)
							return tmp[i].Size();
					}
				}
			}
		}
		return -1;
	}
	return -1;
}

/* if str2 == str1 */
bool GRegExp::isContener(GString str1, GString str2)
{
	if (str2.Size() > str1.Size())
		return false;
	unsigned int i = 0;
	while (i < str2.Size() && str1[i] == str2[i])
		i++;
	if (i == str2.Size())
		return true;
	return false;
}

void GRegExp::addOption(GRegExpOpt &opt)
{
	_opt.PushBack(opt);
}

GString GRegExp::getBurn() const
{
	return _burn;
}
void GRegExp::setBurn(GString burn)
{
	_burn = burn;
}

GString GRegExp::BurnCorner(GString str)
{
	if (_burn.Size() == 0)
		return str;
	GString res;
	int l = burnLeft(str);
	int r = burnRight(str);
	if (r - l <= 0 || r < 0 || l < 0)
		return str;
	for (unsigned int i = (unsigned int)l; i <= (unsigned int)r; i++)
		res += str[i];
	return (GString(res));
}

int GRegExp::burnLeft(GString str)
{
	for (unsigned int i = 0; i < str.Size(); i++)
	{
		bool test = false;
		for (unsigned int j = 0; j < _burn.Size(); j++)
		{
			if (str[i] == _burn[j])
				test = true;
		}
		if (!test)
			return i;
	}
	return -1;
}

int GRegExp::burnRight(GString str)
{
	for (unsigned int i = str.Size(); i > 0; i--)
	{
		bool test = false;
		for (unsigned int j = 0; j < _burn.Size(); j++)
		{
			if (str[i] == _burn[j])
				test = true;
		}
		if (!test)
			return i;
	}
	return -1;
}
