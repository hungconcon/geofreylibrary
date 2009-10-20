

#ifndef __GMAP_H__
# define __GMAP_H__

#include "GExport.h"
#include <iostream>

template<typename T, typename U>
struct GListMap
{
	GListMap(const T &key) : _key(key), _value(U()), _next(NULL), _previous(NULL) {}
	GListMap(const T &key, const U &value) : _value(value), _key(key), _next(NULL), _previous(NULL) {}
	T			_key;
	U			_value;
	GListMap	*_next;
	GListMap	*_previous;
};

template<typename T, typename U>
class GEXPORTED GMap
{
	public:
		GMap(void);
		~GMap(void);
		unsigned int	Size(void) const;
		U				&operator[](const T &Key);
		void			PushBack(const T &Key, const U &Value);
		void			PushFront(const T &Key, const U &Value);
		void			Clear(void);
		bool			IsEmpty(void) const;
		bool			ExistKey(T Key);
		bool			ExistValue(U Value);
		void			EraseKey(T Key);
		void			EraseValue(U Value);
		void			Erase(unsigned int Index);
		int 			IndexOfValue(U Value);
		int				IndexOfKey(T Key);
		T				&FrontKey(void);
		U				&FrontValue(void);
		T				&BackKey(void);
		U				&BackValue(void);
		T				&Key(unsigned int Position);
		U				&Value(unsigned int Position);
		

	private:
		unsigned int	_nbElem;
		GListMap<T, U>	*_begin;
		GListMap<T, U>	*_end;
};

template<typename T, typename U>
GMap<T, U>::GMap(void)
{
	this->_begin = NULL;
	this->_end = NULL;
	this->_nbElem = 0;
}

template<typename T, typename U>
GMap<T, U>::~GMap(void)
{
	GListMap<T, U> *l, *lnext;
	l = this->_begin;
	while (l)
	{
		lnext = l;
		l = l->_next;
		delete lnext;
	}
}

template<typename T, typename U>
void	GMap<T, U>::Clear(void)
{
	GListMap<T, U> *l, *lnext;
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

template<typename T, typename U>
unsigned int GMap<T, U>::Size(void) const
{
	return (this->_nbElem);
}

template<typename T, typename U>
T		&GMap<T, U>::FrontKey(void)
{
	if (this->_nbElem != 0)
		return (this->_begin->_key);
	throw GException("GVector", "Empty vector !");
}

template<typename T, typename U>
U		&GMap<T, U>::FrontValue(void)
{
	if (this->_nbElem != 0)
		return (this->_begin->_value);
	throw GException("GVector", "Empty vector !");
}

template<typename T, typename U>
bool	GMap<T, U>::IsEmpty(void) const
{
	if (this->_nbElem == 0)
		return (true);
	return (false);
}

template<typename T, typename U>
void	GMap<T, U>::PushBack(const T &key, const U &value)
{
	this->_nbElem++;
	if (this->_begin == NULL)
	{
		this->_begin = new GListMap<T, U>(key, value);
		this->_end = this->_begin;
		return ;
	}
	GListMap<T, U> *list = new GListMap<T, U>(key, value);
	list->_previous = this->_end;
	this->_end->_next = list;
	this->_end = list;
}

template<typename T, typename U>
void	GMap<T, U>::PushFront(const T &key, const U &value)
{
	this->_nbElem++;
	if (this->_begin == NULL)
	{
		this->_begin = new GListMap<T, U>(key, value);
		this->_end = this->_begin;
		return ;
	}
	GListMap<T, U> *list = new GListMap<T, U>(key, value);
	list->_next = this->_begin;
	this->_begin->_previous = list;
	this->_begin = list;
}

template<typename T, typename U>
T		&GMap<T, U>::BackKey(void)
{
	if (this->_nbElem != 0)
		return (this->_end->_key);
	throw GException("GVector", "Empty vector !");
}

template<typename T, typename U>
U		&GMap<T, U>::BackValue(void)
{
	if (this->_nbElem != 0)
		return (this->_end->_value);
	throw GException("GVector", "Empty vector !");
}

template<typename T, typename U>
U		&GMap<T, U>::operator[](const T &key)
{
	GListMap<T, U> *l = this->_begin;
	while (l)
	{
		if (key == l->_key)
			return (l->_value);
		l = l->_next;
	}
	this->PushBack(key, U());
	return (this->_end->_value);
}

template<typename T, typename U>
bool	GMap<T, U>::ExistKey(T key)
{
	GListMap<T, U> *l = this->_begin;
	while (l)
	{
		if (key == l->_key)
			return (true);
		l = l->_next;
	}
	return (false);
}

template<typename T, typename U>
bool	GMap<T, U>::ExistValue(U value)
{
	GListMap<T, U> *l = this->_begin;
	while (l)
	{
		if (value == l->_value)
			return (true);
		l = l->_next;
	}
	return (false);
}

template<typename T, typename U>
int 	GMap<T, U>::IndexOfValue(U Value)
{
	unsigned int i = 0;
	GListMap<T, U> *l = this->_begin;
	while (l)
	{
		if (Value == l->_value)
			return (i);
		l = l->_next;
		++i;
	}
	return (-1);
}

template<typename T, typename U>
int		GMap<T, U>::IndexOfKey(T Key)
{
	unsigned int i = 0;
	GListMap<T, U> *l = this->_begin;
	while (l)
	{
		if (Key == l->_key)
			return (i);
		l = l->_next;
		++i;
	}
	return (-1);
}

template<typename T, typename U>
T		&GMap<T, U>::Key(unsigned int index)
{
	unsigned int i = 0;
	GListMap<T, U> *l = this->_begin;
	while (l)
	{
		if (i == index)
			return (l->_key);
		l = l->_next;
		++i;
	}
}

template<typename T, typename U>
U		&GMap<T, U>::Value(unsigned int index)
{
	unsigned int i = 0;
	GListMap<T, U> *l = this->_begin;
	while (l)
	{
		if (i == index)
			return (l->_value);
		l = l->_next;
		++i;
	}
}

template<typename T, typename U>
void	GMap<T, U>::Erase(unsigned int index)
{
	if (index > this->_nbElem)
		throw GException("GVector", "Out of range !");
	this->_nbElem--;
	unsigned int i = 0;
	GListMap<T, U> *l = this->_begin;
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

template<typename T, typename U>
void	GMap<T, U>::EraseKey(T key)
{
	unsigned int i = 0;
	GListMap<T, U> *l = this->_begin;
	while (l)
	{
		if (key == l->_key)
		{
			this->Erase(i);
			return ;
		}
		l = l->_next;
		++i;
	}
}

template<typename T, typename U>
void	GMap<T, U>::EraseValue(U value)
{
	unsigned int i = 0;
	GListMap<T, U> *l = this->_begin;
	while (l)
	{
		if (value == l->_value)
		{
			this->Erase(i);
			return ;
		}
		l = l->_next;
		++i;
	}
}


typedef GMap<unsigned int, unsigned int> GUIntMap;

#endif

