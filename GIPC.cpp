
#include "GIPC.h"

GIPC::GIPC(void) : _fd(NULL)
{
}

GIPC::GIPC(const GString &Name) : _fd(NULL), _name(Name)
{
}

void			GIPC::SetName(const GString &Name)
{
	this->_name = Name;
}

const GString	&GIPC::GetName(void)
{
	return (this->_name);
}

bool			GIPC::Open(bool Read)
{
	if (this->_fd == NULL)
	{
		this->_read = Read;
		char	*tmp = this->_name.ToChar();
		if (this->_read)
#if defined (GWIN)
			fopen_s(&this->_fd, tmp, "r");
#else
			this->_fd = fopen(tmp, "r");
#endif
		else
#if defined (GWIN)
			fopen_s(&this->_fd, tmp, "w");
#else
			this->_fd = fopen(tmp, "w");
#endif
		delete[] tmp;
		if (this->_fd != NULL)
			return (true);
	}
	return (false);
}

bool			GIPC::Close(void)
{
	if (this->_fd != NULL)
	{
		fclose(this->_fd);
		return (true);
	}
	return (false);
}

void			GIPC::Read(void *buffer, unsigned int Size)
{
	if (this->_fd && this->_read && Size && buffer)
	{
		size_t	result = fread(buffer, Size, 1, this->_fd);
		if (result != Size)
			throw GException("GIPC", "Error Fread asked : " + GString(Size) + " Read : " + GString(result));
	}
}

void			GIPC::Write(void *buffer, unsigned int Size)
{
	if (this->_fd && this->_read && Size && buffer)
	{
		size_t	result = fwrite(buffer, Size, 1, this->_fd);
		if (result != Size)
			throw GException("GIPC", "Error FWrite asked : " + GString(Size) + " Write : " + GString(result));
	}
}

void			GIPC::Write(const GString &ToSend)
{
	if (this->_fd && this->_read)
	{
		char	*tmp = ToSend.ToChar();
		size_t	result = fwrite(tmp, ToSend.Size(), 1, this->_fd);
		delete[] tmp;
		if (result != ToSend.Size())
			throw GException("GIPC", "Error FWrite asked : " + GString(ToSend.Size()) + " Write : " + GString(result));
	}
}

