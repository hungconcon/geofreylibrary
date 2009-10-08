
#include "GBase.h"

GString		GBase::HexadecimalToDecimal(const GString &h)
{
	GString Hexa(h);
	GString base("0123456789abcdef");
	int nbr = 0;
	int rec = 0;
	for (int i = (int)Hexa.Size() - 1; i >= 0; --i, ++rec)
	{
		int pos = base.Find(Hexa[i]);
		if (pos == -1)
			return (0);
		nbr += (int)pow((float)16.00, rec) * pos;
	}
	return (GString(nbr));
}

GString		GBase::DecimalToHexadecimal(const GString &h)
{
	GString	Hexa("0123456789abcdef");
	GString	Result;
	int	nbr = h.ToInt();
	while (nbr > 16)
	{
		Result += Hexa[nbr % 16];
		nbr = nbr / 16;
	}
	Result += Hexa[nbr % 16];
	return (Result.Reverse());
}

GString		GBase::BinaryToDecimal(const GString &h)
{
	GString Hexa(h);
	GString base("01");
	int nbr = 0;
	int rec = 0;
	for (int i = (int)Hexa.Size() - 1; i >= 0; --i, ++rec)
	{
		int pos = base.Find(Hexa[i]);
		if (pos == -1)
			return (0);
		nbr += (int)pow((float)2.00, rec) * pos;
	}
	return (GString(nbr));
}

GString		GBase::OctalToDecimal(const GString &h)
{
	GString Hexa(h);
	GString base("01234567");
	int nbr = 0;
	int rec = 0;
	for (int i = (int)Hexa.Size() - 1; i >= 0; --i, ++rec)
	{
		int pos = base.Find(Hexa[i]);
		if (pos == -1)
			return (0);
		nbr += (int)pow((float)8.00, rec) * pos;
	}
	return (GString(nbr));
}
