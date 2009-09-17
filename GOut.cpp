
#include "GOut.h"

GOut::GOut(void)
{

}

GOut::~GOut(void)
{

}

void	GOut::Write(const GString &tab)
{
	/*GString str(tab);
#if defined (GWIN)
	if (_write(1, str.ToChar(), str.Size()) == -1)
#else
	if (write(1, str.ToChar(), str.Size()) == -1)
#endif
	{
		GWarning::Warning("GOut", "Write", "Cannot write on STDIN !");
		return ;	
	}*/
}

void	GOut::WriteLine(const GString &tab)
{
	/*GString str(tab);
	str += "\n";
#if defined (GWIN)
	if (_write(1, str.ToChar(), str.Size()) == -1)
#else
	if (write(1, str.ToChar(), str.Size()) == -1)
#endif
	{
		GWarning::Warning("GOut", "Write", "Cannot write on STDIN !");
		return ;	
	}*/
}

void	GOut::operator <<(const GString &s)
{
	
}


