
#ifndef		__GWAP_HPP__
# define	__GWAP_HPP__

#include "GExport.h"

template<typename T>
void	GEXPORTED GSwap(T &t1, T &t2)
{
	T	tmp(t1);
	t1 = t2;
	t2 = tmp;
}

#endif

