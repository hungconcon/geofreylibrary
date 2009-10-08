
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
	T		_elem;
	GList	*_next;
};

template<typename T>
class GEXPORTED GStack
{
	public:
		GStack(void);
		GStack(T);
		~GStack(void);
		
		void	Push(const T &Elem);
		T		&Top(void);
		T		Pop(void);

	protected:
		GStructStack<T>		*_begin;
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
}

template<typename T>
void	GStack<T>::Push(const T &elem)
{
	GStructStack<T> *list = new GStructStack<T>(elem);
	list->_next = this->_begin;
	this->_begin = list;
}

template<typename T>
T		&GStack<T>::Top(void)
{
	return (this->_begin->elem);	
}

template<typename T>
T		GStack<T>::Pop(void)
{
	T	elem;
	elem = this->_begin->_elem;
	GStructStack<T> *list = this->_begin;
	this->_begin = this->_begin->_next;
	delete list;
	return (elem);	
}

#endif