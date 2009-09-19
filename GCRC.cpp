
#include "GCRC.h"
#include "GBase.h"

GString		GCRC::CalculateCRC16(const GString &Str)
{
	char			crc = 0;
	unsigned int	size = Str.Size();

	for	(unsigned int i = 0 ; i < size ; ++i)
		crc ^= Str[i];

	return GBase::DecimalToHexadecimal((int)crc);
}

GString		GCRC::CalculateCRC32(const GString &Str)
{
	int				crc = 0;
	unsigned int	size = Str.Size();

	for	(unsigned int i = 0 ; i < size ; ++i)
		crc ^= Str[i];
	
	return GBase::DecimalToHexadecimal(crc);
}

GString		GCRC::CalculateCRC64(const GString &Str)
{
	unsigned int	crc = 0;
	unsigned int	size = Str.Size();

	for	(unsigned int i = 0 ; i < size ; ++i)
		crc ^= Str[i];
	
	return GBase::DecimalToHexadecimal(crc);
}

