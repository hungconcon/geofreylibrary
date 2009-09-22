
#ifndef		__GHUFFMAN_H__
# define	__GHUFFMAN_H__

#include "GVector.hpp"
#include "GString.h"

#include <iostream>

struct	GHuffmanStats
{
	long long			_frequence;
	unsigned int		_nbits;
	unsigned int		_code;
	GHuffmanStats(void) : _frequence(0), _nbits(0), _code(0) {}
};

struct	GHuffmanHeader
{
	unsigned int	_size;
	unsigned int	_nbChar;
	char			_extension[4];
};

class	GSheet
{
public:
	GSheet(void);
	GSheet(GSheet *);
	GSheet(long long, unsigned char);
	GSheet(const GSheet &);
	GSheet(GSheet *, GSheet *);
	GSheet(const GSheet &, const GSheet &);
	~GSheet(void);

	long long		GetWeight(void) const;
	unsigned char	GetData(void) const;
	bool			IsNode(void) const;
	bool			operator<=(const GSheet &) const;
	GSheet			&operator=(const GSheet &);
	GSheet			*GetLeft(void);
	GSheet			*GetRight(void);
	void			SetRight(GSheet *);
	void			SetLeft(GSheet *);

	friend std::ostream&	operator<<(std::ostream&, GSheet *);
	friend std::ostream&	operator<<(std::ostream&, const GSheet &);

private:

	long long		_weight;
	bool			_node;
	unsigned char	_data;
	GSheet			*_left;
	GSheet			*_right;
};

class	GHuffman
{
public:
	GHuffman(const GString &);
	~GHuffman(void);
	bool			CreateStats(void);
	bool			CreateTree(void);
	bool			Compress(const GString &);
	bool			Decompress(const GString &);

private:
	void			Calculate(GSheet *, int, int);
	void			BuildTree(GSheet *, int, int, unsigned char);
	bool			Find(unsigned int, unsigned int, GSheet *, unsigned char *);

	GString				_file;
	GHuffmanStats		*_stats;
	GVector<GSheet>		_treeV;
	GSheet				*_tree;
	GString				_content;
	unsigned int		_nbChar;
};

#endif

