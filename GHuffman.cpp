
#include "GHuffman.h"
#include "GFileInfos.h"
#include "GFile.h"

GSheet::GSheet(unsigned int weight, char data) : _weight(weight), _data(data)
{
}

GSheet::GSheet(const GSheet &s)
{
	this->_data = s._data;
	this->_weight = s._weight;
}

bool			GSheet::operator<(const GSheet &s)
{
	if (this->_data < s._data)
		return (true);
	return (false);
}

bool			GSheet::operator<(const GNode &s)
{
	if (this->_weight < s.GetWeight())
		return (true);
	return (false);
}

bool			GSheet::operator==(const GSheet &s)
{
	if (this->_data == s._data && this->_weight == s._weight)
		return (true);
	return (false);
}

GSheet			&GSheet::operator=(const GSheet &s)
{
	this->_data = s._data;
	this->_weight = s._weight;
	return (*this);
}

unsigned int	GSheet::GetWeight(void) const
{
	return (this->_weight);
}

char			GSheet::GetData(void) const
{
	return (this->_data);
}

GNode::GNode(void) : _left(NULL), _right(NULL), _weight(0)
{
}

GNode::GNode(const GSheet &left, const GSheet &right)
{
	this->_left = new GSheet(left);
	this->_right = new GSheet(right);
	this->_weight = this->_left->GetWeight() + this->_right->GetWeight();
}

GNode::GNode(GSheet *left, GSheet *right) : _left(left), _right(right), _weight(0)
{
	if (this->_left)
		this->_weight += this->_left->GetWeight();
	if (this->_right)
		this->_weight += this->_right->GetWeight();
}

GNode::~GNode(void)
{
	if (this->_left)
		delete this->_left;
	if (this->_right)
		delete this->_right;
}

unsigned int	GNode::GetWeight(void) const
{
	return (this->_weight);
}

GHuffman::GHuffman(const GString &file) : _file(file), _tree(NULL), _stats(NULL)
{
}

GHuffman::~GHuffman(void)
{
	if (this->_tree)
		delete this->_tree;
	if (this->_stats)
		delete this->_stats;
}

bool	GHuffman::CreateTree(void)
{
	GFileInfos	f(this->_file);
	if (f.Exist())
	{
		GFile	file(this->_file);
		GString	Data;
		this->_stats = new GHuffmanStats[256];
		while (file.EndOfFile())
		{
			Data = file.Read(500);
			for (unsigned int i = 0; i < Data.Size(); i++)
				this->_stats[Data[i]]._frequence++;
		}
		file.Close();
		return (true);
	}
	return (false);
}

