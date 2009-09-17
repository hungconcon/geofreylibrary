
#include "GLoadLibrary.h"

bool	GLoadLibrary::LdLibrary(const GString &lib)
{
	GString Library;
	if (this->_test == false)
		Library = this->_directory + lib;
	else
		Library = lib;
#if defined (GWIN)
	GFileInfos d;
	if (!Library.EndWith(".dll"))
		d.SetFile(Library + ".dll");
	else
		d.SetFile(Library);
	if (!d.Exist())
		return (false);
	Library = Library.Replace(".dll", "");
	int f = Library.LastIndexOf("/");
	if (f != GString::NotFound)
		Library = Library.Substr(f + 1);
	if (!this->_map.ExistKey(Library))
	{
		char	*tmp = d.FileName().ToChar();
		GLibrary fct = ::LoadLibrary(tmp);
		delete[] tmp;
		if (fct == NULL)
		{
			GString Error("Cannot load " + Library + " !");
			GWarning::Warning("GLoadLibrary", "LoadLibrary", Error.ToChar());
			return (false);
		}
		this->_map[Library] = fct;
		GString Error("Library " + Library + " has been loaded !");
		GWarning::Warning("GLoadLibrary", "LoadLibrary", Error.ToChar());
		return (true);
	}
	GString Error("Library " + Library + " is already loaded !");
	GWarning::Warning("GLoadLibrary", "LoadLibrary", Error.ToChar());
	return (false);
#else
	GFileInfos d;
	if (!Library.EndWith(".so"))
		d.SetFile(Library + ".so");
	else
		d.SetFile(Library);
	if (!d.Exist())
		return (false);
	Library = Library.Replace(".so", "");
	int f = Library.LastIndexOf("/");
	if (f != GString::NotFound)
		Library = Library.Substr(f + 1);
	if (!this->_map.ExistKey(Library))
	{
		char		*tmp = d.FileName().ToChar();
	    GLibrary	fct = dlopen(tmp, RTLD_LAZY);
		delete[]	tmp;
		if (fct == NULL)
		{
			GString Error("Cannot load " + d.FileName() + " !");
			GWarning::Warning("GLoadLibrary", "LoadLibrary", Error.ToChar());
			return (false);
		}
		this->_map[Library] = fct;
		GString Error("Library " + d.FileName() + " has been loaded !");
		GWarning::Warning("GLoadLibrary", "LoadLibrary", Error.ToChar());
		return (true);
	}
	GString Error("Library " + d.FileName() + " is already loaded !");
	GWarning::Warning("GLoadLibrary", "LoadLibrary", Error.ToChar());
	return (false);
#endif
}

GLoadLibrary::GLoadLibrary(void)
{
	this->_directory = "./";
	this->_test = false;
}

GLoadLibrary::~GLoadLibrary(void)
{

}

void	GLoadLibrary::LoadAllLibrary(void)
{
	this->_test = true;
	GDirectory dir;
	dir.Cd(this->_directory);
	GFileList list = dir.Ls();
	for (unsigned int i = 0 ; i < list.Size(); ++i)
		this->LdLibrary(list[i].FileName());
	this->_test = false;
}

GLibrary	GLoadLibrary::GetLibrary(const GString &Library)
{
	if (this->_map.ExistKey(Library))
	{
		GString Error("Library " + Library + " has been found !");
		GWarning::Warning("GLoadLibrary", "GetLibrary", Error.ToChar());
		return (this->_map[Library]);
	}
	GString Error("Library " + Library + " doesn't exist !");
	GWarning::Warning("GLoadLibrary", "GetLibrary", Error.ToChar());
	return (0);
}

GMethod	GLoadLibrary::GetFunction(const GString &Library, const GString &Method)
{
	if (this->_map.ExistKey(Library))
	{
		GString Error("Library " + Library + " has been found !");
		GWarning::Warning("GLoadLibrary", "GetLibrary", Error.ToChar());
		char	*tmp = Method.ToChar();
		#if defined (WIN32) | defined (_WIN32) |  defined (__WIN32) | defined (WIN64) | defined (_WIN64) | defined (__WIN64)
			GMethod fct = (GMethod)GetProcAddress(this->_map[Library], tmp);
		#else
			GMethod fct = (GMethod)dlsym(this->_map[Library], tmp);
		#endif
		delete[] tmp;
		if (fct == NULL)
		{
			GString Error("Cannot find " + Method + " in library " + Library + " !");
			GWarning::Warning("GLoadLibrary", "GetLibrary", Error.ToChar());
			return (NULL);
		}
		return (fct);
	}
	GString Error("Library " + Library + " doesn't exist !");
	GWarning::Warning("GLoadLibrary", "GetLibrary", Error.ToChar());
	return (0);
}

GMethod	GLoadLibrary::GetFunction(GLibrary Library, const GString &Method)
{
	char	*tmp = Method.ToChar();
	#if defined (GWIN)
		GMethod fct = (GMethod)GetProcAddress(Library, tmp);
	#else
		GMethod fct = (GMethod)dlsym(Library, tmp);
	#endif
	delete[] tmp;
	if (fct == NULL)
	{
		GString Error("Cannot find " + Method + " in library !");
		GWarning::Warning("GLoadLibrary", "GetLibrary", Error.ToChar());
		return (NULL);
	}
	return (fct);
}

void		GLoadLibrary::UnloadLibrary(const GString &Library)
{
	if (this->_map.ExistKey(Library))
	{
		GString Error("Library " + Library + " has been unloaded !");
		GWarning::Warning("GLoadLibrary", "GetLibrary", Error.ToChar());
#if defined (GWIN)
		FreeLibrary(this->_map[Library]);
#else
		dlclose(this->_map[Library]);
#endif
		this->_map.EraseKey(Library);
		return ;
	}
	GString Error("Library " + Library + " doesn't exist !");
	GWarning::Warning("GLoadLibrary", "UnloadLibrary", Error.ToChar());
}

void	GLoadLibrary::SetDirectory(const GString &Directory)
{
	this->_directory = Directory;
	if (!this->_directory.EndWith("/"))
		this->_directory += "/";
}

GLoadLibrary::GLoadLibrary(const GString &Directory)
{
	this->_directory = Directory;
	if (!this->_directory.EndWith("/"))
		this->_directory += "/";
	this->_test = false;
}
