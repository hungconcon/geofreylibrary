
#include "GIPC.h"
#include "GSleep.h"

GMutex			GIPC::_mutex = GMutex();

#if defined	(GWIN)
GMap<GString, GVector<HANDLE> >		GIPC::_map = GMap<GString, GVector<HANDLE> >();
#else
GMap<GString, GVEctor<int> >			GIPC::_map = GMap<GString, GVector<int> >();
#endif

GIPC::GIPC(const GString &Name) : _name(Name), _read(true)
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

void			GIPC::SetMode(bool Read)
{
	this->_read = Read;
}

bool			GIPC::Start(void)
{
	this->_mutex.Lock();
	bool	exist(this->_map.ExistKey(this->_name));
	this->_mutex.Unlock();
	if (!exist)
	{
	#if defined (GWIN)
		SECURITY_ATTRIBUTES sa;
		sa.bInheritHandle = TRUE;
		sa.lpSecurityDescriptor = 0;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		HANDLE	pip[2];
		if (!CreatePipe(&pip[0], &pip[1], &sa, 0))
			return (false);
	#else
		int		pip[2];
		if (pipe(pip) == -1)
			return (false);
	#endif
		this->_mutex.Lock();
		this->_map[this->_name].PushBack(pip[0]);
		this->_map[this->_name].PushBack(pip[1]);
		this->_mutex.Unlock();
		return (true);
	}
	return (false);
}

bool			GIPC::IsReadable(void)
{
	if (this->_read)
	{
		this->_mutex.Lock();
		bool	exist(this->_map.ExistKey(this->_name));
		this->_mutex.Unlock();
		if (!exist)
			return (false);
		bool	ok(true);
		this->_mutex.Lock();
		if (!GetFileSize(this->_map[this->_name][0], NULL))
			ok = false;
		this->_mutex.Unlock();
		return (ok);
	}
	return (false);
}

bool			GIPC::Read(void *buffer, unsigned int Size)
{
	if (this->_read && Size && buffer)
	{
		this->_mutex.Lock();
		bool	exist(this->_map.ExistKey(this->_name));
		this->_mutex.Unlock();
		if (exist)
		{
			while (!this->IsReadable())
				GUSleep(100);
			this->_mutex.Lock();
#if defined (GWIN)
			DWORD	result;
			ReadFile(this->_map[this->_name][0], buffer, Size, &result, NULL);
#else
			size_t	result = read(buffer, Size, this->_map[this->_name][0]);
#endif
			this->_mutex.Unlock();
			if (result != Size)
				throw GException("GIPC", "Error Fread asked : " + GString(Size) + " Read : " + GString(result));
			return (true);
		}
	}
	return (false);
}

bool			GIPC::Write(void *buffer, unsigned int Size)
{
	if (!this->_read && Size && buffer)
	{
		this->_mutex.Lock();
		bool	exist(this->_map.ExistKey(this->_name));
		this->_mutex.Unlock();
		if (exist)
		{
			this->_mutex.Lock();
#if defined (GWIN)
			DWORD	result;
			WriteFile(this->_map[this->_name][1], buffer, Size, &result, NULL);
#else
			size_t	result = fwrite(buffer, Size, 1, this->_map[this->_name][1]);
#endif
			this->_mutex.Unlock();
			if (result != Size)
				throw GException("GIPC", "Error FWrite asked : " + GString(Size) + " Write : " + GString(result));
			return (true);
		}
	}
	return (false);
}

bool			GIPC::Write(const GString &ToSend)
{
	if (!this->_read && !ToSend.IsEmpty())
	{
		this->_mutex.Lock();
		bool	exist(this->_map.ExistKey(this->_name));
		this->_mutex.Unlock();
		if (exist)
		{
			char	*tmp = ToSend.ToChar();
			this->_mutex.Lock();
#if defined (GWIN)
			DWORD	result;
			WriteFile(this->_map[this->_name][1], tmp, ToSend.Size(), &result, NULL);
#else
			size_t	result = fwrite(tmp, ToSend.Size(), 1, this->_map[this->_name][1]);
#endif
			this->_mutex.Unlock();
			delete[] tmp;
			if (result != ToSend.Size())
				throw GException("GIPC", "Error FWrite asked : " + GString(ToSend.Size()) + " Write : " + GString(result));
			return (true);
		}
	}
	return (false);
}

