
#ifndef __GVECTOR_H__
# define __GVECTOR_H__

#include <iostream>
#include <vector>
#include "GWarning.h"
#include "GException.h"
#include "GExport.h"

template<typename T>
struct GList
{
	GList(const T &elem) : _elem(elem), _next(NULL), _previous(NULL) {}
	T		_elem;
	GList	*_next;
	GList	*_previous;
};

template<typename T>
class GEXPORTED GVector
{
	public:
		GVector(void);
		GVector(T);
		GVector(const GVector<T> &);
		GVector(const std::vector<T> &);
		~GVector(void);
		
		void			PushFront(T);
		void			PushBack(T);
		void			Clear(void);
		void			Erase(unsigned int);
		void			Delete(const T &);
		bool			Contain(const T &) const;
		bool			IsEmpty(void) const;
		void			Insert(unsigned int, const T &);
		T				PopFront(void);
		T				PopBack(void);
		std::vector<T>	ToStdVector(void) const;
		T				Front(void) const;
		T				Back(void) const;
		int				IndexOf(T) const;
		unsigned int	Size(void) const;
		void			Sort(G::OrderOption = G::ORDER_ASC);
		T				&operator[](unsigned int);
		GVector<T>		operator=(const GVector<T> &);
		bool			operator==(const GVector<T> &);
		bool			operator!=(const GVector<T> &);
		GVector<T>		operator+(const GVector<T> &);
		GVector<T>		operator+(const T &);
		GVector<T>		&operator+=(const T &);
		GVector<T>		&operator+=(const GVector<T> &);
		GVector<T>		&operator<<(const T &);
		GVector<T>		&operator<<(const GVector<T> &);

	protected:
		unsigned int	_nbElem;
		GList<T>		*_begin;
		GList<T>		*_end;
};

template<typename T>
GVector<T>::GVector(void)
{
	this->_begin = NULL;
	this->_end = NULL;
	this->_nbElem = 0;
}

template<typename T>
GVector<T>::GVector(T elem)
{
	this->_nbElem = 1;
	GList<T> *list = new GList<T>(elem);
	this->_begin = list;
	this->_end = list;
}
template<typename T>
GVector<T>::~GVector(void)
{
	GList<T> *l, *lnext;
	l = this->_begin;
	while (l)
	{
		lnext = l;
		l = l->_next;
		delete lnext;
	}
}
template<typename T>
void	GVector<T>::Clear(void)
{
	GList<T> *l, *lnext;
	l = this->_begin;
	while (l)
	{
		lnext = l;
		l = l->_next;
		delete lnext;
	}
	this->_begin = NULL;
	this->_end = NULL;
	this->_nbElem = 0;
}
template<typename T>
unsigned int GVector<T>::Size(void) const
{
	return (this->_nbElem);
}

template<typename T>
T	GVector<T>::Front(void) const
{
	if (this->_nbElem != 0)
		return (this->_begin->_elem);
	throw GException("GVector", "Empty vector !");
}
template<typename T>
T	GVector<T>::Back(void) const
{
	if (this->_nbElem != 0)
		return (this->_end->_elem);
	throw GException("GVector", "Empty vector !");
}
template<typename T>
bool	GVector<T>::IsEmpty(void) const
{
	if (this->_nbElem == 0)
		return (true);
	return (false);
}

template<typename T>
bool	GVector<T>::Contain(const T &e) const
{
	GList<T> *l = this->_begin;
	T test(e);
	while (l)
	{
		if (l->_elem == test)
			return (true);
		l = l->_next;
	}
	return (false);
}


template<typename T>
int	GVector<T>::IndexOf(T e) const
{
	GList<T> *l = this->_begin;
	T test(e);
	unsigned int i = 0;
	while (l)
	{
		if (l->_elem == test)
			return (i);
		l = l->_next;
		++i;
	}
	return (-1);
}
template<typename T>
void	GVector<T>::PushBack(T elem)
{
	this->_nbElem++;
	if (this->_begin == NULL)
	{
		this->_begin = new GList<T>(elem);
		this->_end = this->_begin;
		return ;
	}
	GList<T> *list = new GList<T>(elem);
	list->_previous = this->_end;
	this->_end->_next = list;
	this->_end = list;
}
template<typename T>
void	GVector<T>::PushFront(T elem)
{
	this->_nbElem++;
	if (this->_begin == NULL)
	{
		this->_begin = new GList<T>(elem);
		return ;
	}
	GList<T> *list = new GList<T>(elem);
	list->_next = this->_begin;
	this->_begin->_previous = list;
	this->_begin = list;
}
template<typename T>
T	GVector<T>::PopFront(void)
{
	if (this->_nbElem != 0)
	{
		T save = this->_begin->_elem;
		this->Erase(0);
		return (save);
	}
	throw GException("GVector", "Vector is Empty");
}
template<typename T>
T	GVector<T>::PopBack(void)
{
	if (this->_nbElem != 0)
	{
		T save = this->_end->_elem;
		this->Erase(this->_nbElem - 1);
		return (save);
	}
	throw GException("GVector", "Vector is Empty");
}
template<typename T>
GVector<T>::GVector(const GVector &v)
{
	this->_begin = NULL;
	this->_nbElem = 0;
	this->_end = NULL;
	GList<T> *l = v._begin;
	while (l)
	{
		this->PushBack(l->_elem);
		l = l->_next;
	}
}
template<typename T>
std::vector<T>	GVector<T>::ToStdVector(void) const
{
	std::vector<T> vec;
	GList<T> *l = this->_begin;
	while (l)
	{
		vec.push_back(l->_elem);
		l = l->_next;
	}
	return (vec);
}

template<typename T>
GVector<T>::GVector(const std::vector<T> &v)
{
	this->_nbElem = 0;
	this->_begin = NULL;
	this->_end = NULL;
	for (unsigned int i = 0; i < v.size(); ++i)
		this->PushBack(v[i]);
}
template<typename T>
void	GVector<T>::Insert(unsigned int index, const T &elem)
{
	this->_nbElem++;
	if (index < this->_nbElem)
	{
		GList<T> *l = this->_begin;
		unsigned int i = 0;
		while (l)
		{
			if (index == i)
			{
				GList<T> *list = new GList<T>(elem);
				list->_next = l->_next;
				list->_previous = l;
				l->_next = list;
				return;
			}
			l = l->_next;
			++i;
		}
	}
	else
		this->PushBack(elem);
}




template<typename T>
void	GVector<T>::Erase(unsigned int index)
{
	if (index > this->_nbElem)
		throw GException("GVector", "Out of range !");
	this->_nbElem--;
	unsigned int i = 0;
	GList<T> *l = this->_begin;
	while (l)
	{
		if (i == index)
		{
			if (l->_previous != NULL && l->_next != NULL)
			{
				l->_previous->_next = l->_next;
				l->_next->_previous = l->_previous;
				delete l;
				return ;
			}
			else if (l->_previous == NULL && l->_next == NULL)
			{
				delete l;
				this->_nbElem = 0;
				this->_begin = NULL;
				this->_end = NULL;
				return ;
			}
			else if (l->_next == NULL)
			{
				l->_previous->_next = NULL;
				this->_end = l->_previous;
				delete l;
				return ;
			}
			else if (l->_previous == NULL)
			{
				l->_next->_previous = NULL;
				this->_begin = l->_next;
				delete l;
				return ;
			}
		}
		l = l->_next;
		++i;
	}
}





template<typename T>
void	GVector<T>::Delete(const T &e)
{
	bool test = true;
	unsigned int i;
	while (test)
	{
		i = 0;
		test = false;
		GList<T> *l = this->_begin;
		
		while (l)
		{
			if (l->_elem == e)
			{
				this->Erase(i);
				test = true;
			}
			l = l->_next;
			++i;
		}
	}	
}

template<typename T>
void	GVector<T>::Sort(G::OrderOption g)
{
	bool test = true;
	while (test)
	{
		test = false;
		if (this->_nbElem > 1)
		{
			GList<T> *l = this->_begin;
			l = l->_next;
			if (g == G::ORDER_ASC)
			{
				while (l)
				{
					if (l->_elem < l->_previous->_elem)
					{
						T save = l->_elem;
						l->_elem = l->_previous->_elem;
						l->_previous->_elem = save;
						test = true;
					}
					l = l->_next;
				}
			}
			else
			{
				while (l)
				{
					if (l->_elem > l->_previous->_elem)
					{
						T save = l->_elem;
						l->_elem = l->_previous->_elem;
						l->_previous->_elem = save;
						test = true;
					}
					l = l->_next;
				}
			}
		}
	}
}




template<typename T>
T		&GVector<T>::operator[](unsigned int index)
{	
	if (index > this->_nbElem)
		index = this->_nbElem - 1;
	unsigned int i = 0;
	GList<T> *l = this->_begin;
	while (l)
	{
		if (i == index)
			return (l->_elem);
		l = l->_next;
		++i;
	}
	return (l->_elem);
}



template<typename T>
bool	GVector<T>::operator==(const GVector<T> &v)
{
	if (this->_nbElem != v._nbElem)
		return (false);
	GList<T> *l1 = this->_begin;
	GList<T> *l2 = v._begin;
	while (l1)
	{
		if (l1->_elem != l2->_elem)
			return (false);
		l1 = l1->_next;
		l2 = l2->_next;
	}
	return (true);
}


template<typename T>
GVector<T>	GVector<T>::operator=(const GVector<T> &v)
{
	this->_begin = NULL;
	this->_nbElem = 0;
	this->_end = NULL;
	GList<T> *l = v._begin;
	while (l)
	{
		this->PushBack(l->_elem);
		l = l->_next;
	}
	return (*this);
}


template<typename T>
bool	GVector<T>::operator!=(const GVector<T> &v)
{
	if (this->_nbElem == v._nbElem)
		return (false);
	GList<T> *l1 = this->_begin;
	GList<T> *l2 = v._begin;
	bool test = false;
	while (l1)
	{
		if (l1->_elem != l2->_elem)
			return (true);
		l1 = l1->_next;
		l2 = l2->_next;
	}
	return (false);
}

template<typename T>
GVector<T>		&GVector<T>::operator+=(const T &elem)
{
	this->PushBack(elem);
	return (*this);
}

template<typename T>
GVector<T>		&GVector<T>::operator+=(const GVector<T> &vec)
{
	GList<T> *l = vec._begin;
	while (l)
	{
		this->PushBack(l->_elem);
		l = l->_next;
	}
	return (*this);
}

template<typename T>
GVector<T>		&GVector<T>::operator<<(const T &elem)
{
	this->PushBack(elem);
	return (*this);
}

template<typename T>
GVector<T>		&GVector<T>::operator<<(const GVector<T> &vec)
{
	GList<T> *l = vec._begin;
	while (l)
	{
		this->PushBack(l->_elem);
		l = l->_next;
	}
	return (*this);
}


template<typename T>
GVector<T>		GVector<T>::operator+(const GVector<T> &vec)
{
	GVector<T> newvec;
	GList<T> *l = this->_begin;
	while (l)
	{
		newvec.PushBack(l->_elem);
		l = l->_next;
	}
	l = vec._begin;
	while (l)
	{
		newvec.PushBack(l->_elem);
		l = l->_next;
	}
	return (newvec);
}

template<typename T>
GVector<T>		GVector<T>::operator+(const T &vec)
{
	GVector<T> newvec;
	GList<T> *l = this->_begin;
	while (l)
	{
		newvec.PushBack(l->_elem);
		l = l->_next;
	}
	newvec.PushBack(vec);
	return (newvec);
}

#endif
