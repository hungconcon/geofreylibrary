
#include "GFile.h"

GFile::GFile(const GString &f) : _file(f), _pFile(NULL), _open(false)
{
}

GFile::GFile(void) : _pFile(NULL), _open(false)
{
}


GFile::~GFile(void)
{
	this->Close();
}

void	GFile::SetFile(const GString &file)
{
	this->Close();
	this->_file = file;
}

GString	GFile::GetName(void)
{
	return (this->_file);
}

bool	GFile::Rm(const GString &f)
{
	bool	ok(true);
	char	*tmp = f.ToChar();
#if defined (GWIN)
	if (DeleteFile(tmp) == 0)
		ok = false;
#else
	if (unlink(tmp) == -1)
		ok = false;
#endif
	delete[] tmp;
	return (ok);
}


bool	GFile::Rm(void)
{
	if (this->_open || this->_pFile == NULL)
		this->Close();
	bool	ok(true);
	char	*tmp = this->_file.ToChar();
#if defined (GWIN)
	if (DeleteFile(tmp) == 0)
		ok = false;
#else
	if (unlink(tmp) == -1)
		ok = false;
#endif
	delete[] tmp;
	return (ok);
}

bool	GFile::Create(const GString &file)
{
	FILE	*pFile;
	char	*tmp = file.ToChar();
#if defined (GWIN)
	fopen_s(&pFile, tmp, "a");
#else
	pFile = fopen(tmp, "a");
#endif
	delete[] tmp;
	if (pFile == NULL)
		return (false);
	fclose(pFile);
	pFile = NULL;
	return (true);
}

void	GFile::Open(bool Binary)
{
	if (this->_open == false)
	{
		if (Binary == false)
			this->_mode = "a+";
		else
			this->_mode = "a+b";
		char	*mode = this->_mode.ToChar();
		char	*file = this->_file.ToChar();
#if defined (GWIN)
		fopen_s(&this->_pFile, file, mode);
#else
		this->_pFile = fopen(file, mode);
#endif
		delete[] mode;
		delete[] file;
		if (this->_pFile == NULL)
		{
			this->_open = false;
			throw GException("GFile", "Cannot open file " + this->_file);
		}
		this->_open = true;
	}
}

void	GFile::Clear(void)
{
	this->Close();
	this->Rm();
	this->Open(true);
}

void	GFile::Close(void)
{
	if (this->_open == true)
	{
		this->_open = false;
		if (this->_pFile)	
			if (fclose(this->_pFile) != 0)
			{
				this->_pFile = NULL;
				throw GException("GFile", "Error on fclose()");
			}
		this->_pFile = NULL;
	}
}

GString	GFile::Read(void)
{
	if (this->_open && this->_pFile)
	{
		long		lSize;
		char		*buffer;
		size_t		result;
		this->GoToEnd();
		if ((lSize = ftell(this->_pFile)) == (long)-1)
		{
			this->_open = false;
			throw GException("GFile", "Error ftell()");
		}
		this->GoToBegin();
		buffer = new char[lSize + 1];
		result = fread(buffer, 1, lSize, this->_pFile);
		if (result != lSize)
		{
			this->_open = false;
			delete[] buffer;
			throw GException("GFile", "Reading error ! Read : " + GString(result) + " SizeFile : " + GString(lSize));
		}
		GString	ret(GString::GetBuffer(buffer, lSize));
		delete[] buffer;
		return (ret);
	}
	else
		throw GException("GFile", "This file is not open !");
	return ("");
}

GString	GFile::Read(unsigned int Size)
{
	if (this->_open && this->_pFile)
	{
		char		*buffer;
		size_t		result;
		buffer = new char[Size + 1];
		result = fread(buffer, 1, Size, this->_pFile);
		if (result == 0)
		{
			this->_open = false;
			delete[] buffer;
			throw GException("GFile", "Reading error ! Read : " + GString(result) + " Size Asked : " + GString(Size));
		}
		GString	ret(GString::GetBuffer(buffer, result));
		delete[] buffer;
		return (ret);
	}
	else
		throw GException("GFile", "This file is not open !");
	return ("");
}

void	GFile::Read(void *Pointeur, unsigned int Size)
{
	if (this->_open && this->_pFile)
	{
		size_t result = fread(Pointeur, 1, Size, this->_pFile);
		if (result == 0)
		{
			this->_open = false;
			throw GException("GFile", "Reading error ! Read : " + GString(result) + " Size Asked : " + GString(Size));
		}
	}
}

void	GFile::Write(const GString &ToWrite)
{
	if (this->_open && this->_pFile)
	{
		char *tmp = ToWrite.ToChar();
		fwrite(tmp, 1, ToWrite.Size(), this->_pFile);
		delete[] tmp;
	}
}

void	GFile::Write(void *Pointeur, unsigned int Size)
{
	if (this->_open && this->_pFile)
		fwrite(Pointeur, 1, Size, this->_pFile);
}

bool	GFile::IsOpen(void) const
{
	return (this->_open && this->_pFile);
}

void	GFile::GoToBegin(void)
{
	if (this->_open && this->_pFile)
		if (fseek(this->_pFile, 0, SEEK_SET) != 0)
		{
			this->_open = false;
			throw GException("GFile", "Error GotToBegin");
		}
}

void	GFile::GoToEnd(void)
{
	if (this->_open && this->_pFile)
		if (fseek(this->_pFile, 0, SEEK_END) != 0)
		{
			this->_open = false;
			throw GException("GFile", "Error GoToEnd");
		}
}

void	GFile::GoTo(unsigned int Position)
{
	if (this->_open && this->_pFile)
		if (fseek(this->_pFile, Position, SEEK_SET) != 0)
		{
			this->_open = false;
			throw GException("GFile", "Error GoTo " + Position);
		}
}

long	GFile::CurrentIndex(void)
{
	if (this->_open && this->_pFile)
	{
		long	lSize;
		if ((lSize = ftell(this->_pFile)) == (long)-1)
		{
			this->_open = false;			
			throw GException("GFile", "Error ftell()");
		}
		return (lSize);
	}
	return (-1);
}


bool	GFile::EndOfFile(void)
{
	if (this->_open && this->_pFile)
		if (feof(this->_pFile))
			return (true);
	return (false);
}