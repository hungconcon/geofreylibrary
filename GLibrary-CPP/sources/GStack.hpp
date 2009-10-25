
#ifndef __GSTACK_H__
# define __GSTACK_H__

#include <iostream>
#include <stack>
#include "GWarning.h"
#include "GException.h"
#include "GExport.h"

template<typename T>
struct GStructStack
{
	GStructStack(const T &elem) : _elem(elem), _next(NULL){}
	T					_elem;
	GStructStack<T>		*_next;
};

template<typename T>
class GEXPORTED GStack
{
	public:
		GStack(void);
		GStack(const T &Elem);
		~GStack(void);
		
		void			Push(const T &Elem);
		T				&Top(void);
		T				Pop(void);
		unsigned int	Size(void) const;

	protected:
		GStructStack<T>		*_begin;
		unsigned int		_size;
};

template<typename T>
GStack<T>::GStack(void)
{
	this->_begin = NULL;
}

template<typename T>
GStack<T>::GStack(const T &elem)
{
	GStructStack<T> *list = new GStructStack<T>(elem);
	this->_begin = list;
	this->_size = 1;
}

template<typename T>
GStack<T>::~GStack(void)
{

}

template<typename T>
unsigned int	GStack<T>::Size(void) const
{
	return (this->_size);
}

template<typename T>
void	GStack<T>::Push(const T &elem)
{
	GStructStack<T> *list = new GStructStack<T>(elem);
	list->_next = this->_begin;
	this->_begin = list;
	++this->_size;
}

template<typename T>
T		&GStack<T>::Top(void)
{
	return (this->_begin->_elem);	
}

template<typename T>
T		GStack<T>::Pop(void)
{
	if (this->_size)
	{
		T	elem;
		elem = this->_begin->_elem;
		GStructStack<T> *list = this->_begin;
		this->_begin = this->_begin->_next;
		delete list;
		return (elem);
	}
	return (T());
}

#endif