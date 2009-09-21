
#ifndef		__GHUFFMAN_H__
# define	__GHUFFMAN_H__

#include "GVector.hpp"
#include "GString.h"

struct	GHuffmanStats
{
	long long			_frequence;
	GHuffmanStats(void) : _frequence(0) {}
};

class	GNode;

class	GSheet
{
public:
	GSheet(unsigned int, char);
	GSheet(const GSheet &);
	unsigned int	GetWeight(void) const;
	char			GetData(void) const;
	bool			operator<(const GSheet &);
	bool			operator<(const GNode &);
	bool			operator==(const GSheet &);
	GSheet			&operator=(const GSheet &);

private:
	unsigned int	_weight;
	char			_data;
};

class	GNode
{
public:
	GNode(void);
	~GNode(void);
	GNode(const GSheet &, const GSheet &);
	GNode(GSheet *, GSheet *);
	unsigned int	GetWeight(void) const;

private:
	unsigned int	_weight;
	GSheet			*_left;
	GSheet			*_right;
};

class	GHuffman
{
public:
	GHuffman(const GString &);
	~GHuffman(void);
	bool			CreateTree(void);

private:
	GString			_file;
	GHuffmanStats	*_stats;
	GNode			*_tree;
};

#endif

