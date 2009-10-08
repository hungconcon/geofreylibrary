
#include "GIPC.h"
#include "GSleep.h"
#include "GFileInfos.h"

namespace GIPC
{
	GMutex			GPipe::_mutex = GMutex();

	#if defined	(GWIN)
	GMap<GString, GVector<HANDLE> >			GPipe::_map = GMap<GString, GVector<HANDLE> >();
	#else
	GMap<GString, GVector<int> >			GPipe::_map = GMap<GString, GVector<int> >();
	#endif

	GPipe::GPipe(const GString &Name) : _name(Name)
	{
		this->_read = true;
	}

	void			GPipe::SetName(const GString &Name)
	{
		this->_name = Name;
	}

	const GString	&GPipe::GetName(void)
	{
		return (this->_name);
	}

	void			GPipe::SetMode(bool Read)
	{
		this->_read = Read;
	}

	bool			GPipe::Start(void)
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

	bool			GPipe::IsReadable(void)
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
#if defined (GWIN)
			if (!GetFileSize(this->_map[this->_name][0], NULL))
				ok = false;
#else
			GFileInfos	f(this->_name);
			if (f.Size() > 0)
				ok = false;
#endif
			this->_mutex.Unlock();
			return (ok);
		}
		return (false);
	}

	bool			GPipe::Read(void *buffer, unsigned int Size)
	{
		if (this->_read && Size && buffer)
		{
			this->_mutex.Lock();
			bool exist(this->_map.ExistKey(this->_name));
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
				size_t result = read(this->_map[this->_name][0], buffer, Size);
	#endif
				this->_mutex.Unlock();
				if (result != Size)
					throw GException("GIPC", "Error Fread asked : " + GString(Size) + " Read : " + GString(result));
				return (true);
			}
		}
		return (false);
	}

	bool			GPipe::Write(void *buffer, unsigned int Size)
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
				size_t	result = write(this->_map[this->_name][1], buffer, Size);
	#endif
				this->_mutex.Unlock();
				if (result != Size)
					throw GException("GIPC", "Error FWrite asked : " + GString(Size) + " Write : " + GString(result));
				return (true);
			}
		}
		return (false);
	}

	bool			GPipe::Write(const GString &ToSend)
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
				size_t	result = write(this->_map[this->_name][1], tmp, ToSend.Size());
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
#if defined (GWIN)
#else
	unsigned int	GSemaphore::_sum = 0;
#endif

	GSemaphore::GSemaphore(unsigned int nb, const GString &Name) : _name(Name), _nb(nb)
	{
		char	*tmp = this->_name.ToChar();
#if defined (GWIN)
		this->_semid = CreateSemaphore(NULL, 1, this->_nb, tmp);
		if (this->_semid == NULL)
			throw GException("GSemaphore", "Error Creation Semaphore");
#else
		this->_key = ftok(tmp, 'G');
		this->_semid = semget(this->_key, 1, IPC_CREAT | IPC_EXCL | 0666);
		if (this->_semid == -1)
			throw GException("GSemaphore", "Error Creation Semaphore");
		semctl(this->_semid, 0, SETVAL, 1);
		this->_num = this->_sum;
		this->_sum++;
#endif
		delete[] tmp;
	}

	bool	GSemaphore::Lock(void)
	{
#if defined (GWIN)
		WaitForSingleObject(this->_semid, INFINITE);
		return (true);
#else
		sembuf op;
		op.sem_num = this->_num;
		op.sem_op = -1;
		op.sem_flg = 0;
		if (semop(this->_semid, &op, 1) == 0)
			return (true);
#endif
		return (false);
	}

	bool	GSemaphore::Unlock(void)
	{
#if defined (GWIN)
		if (ReleaseSemaphore(this->_semid, 1, NULL) != 0)
			return (true);
#else
		sembuf op;
		op.sem_num = this->_num;
		op.sem_op = 1;
		op.sem_flg = 0;
		if (semop(this->_semid, &op, 1) == 0)
			return (true);
#endif
		return (false);
	}

}

