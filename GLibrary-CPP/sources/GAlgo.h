
#ifndef __GALGO_H__
# define __GALGO_H__

#include "GString.h"
#include "GMap.hpp"
class GAlgo
{
	public:
		static	int				PGCD(int, int);
		static	GStringList		GStringToNPI(const GString &);
		static	GStringList		GStringToArray(const GString &);
		static	int				GStringToInt(const GString &);
		static	unsigned int	Pow(unsigned int Nbr, unsigned int Pow);
	private:

};

#endif
