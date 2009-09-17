
#include "GProcessus.h"

GProcessus::GProcessus(unsigned int PID, const GString &Path)
{
	this->_pid = PID;
	this->_path = Path;
}

GProcessus::~GProcessus(void)
{
	
}

GString		GProcessus::GetPath(void) const
{
	return (this->_path);
}

unsigned int GProcessus::GetPID(void) const
{
	return (this->_pid);
}


void	GProcessus::Run(const GString &name, const GString &param)
{
	CreateProcess(name.ToLPCSTR(), param.ToChar(), NULL, NULL, false, NULL, NULL, NULL, NULL, NULL);
}

GStringList		GProcessus::List(void)
{

}

