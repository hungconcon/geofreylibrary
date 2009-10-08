
#ifndef __GBASE_H__
# define __GBASE_H__

#include "GString.h"
#include <cmath>

class GBase
{
	public:
		static GString		HexadecimalToDecimal(const GString &Hexadecimal);
		static GString		BinaryToDecimal(const GString &Binary);
		static GString		OctalToDecimal(const GString &Octal);
		static GString		DecimalToHexadecimal(const GString &Decimal);
};

#endif
