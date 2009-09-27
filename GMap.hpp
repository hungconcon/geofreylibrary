

#ifndef __GMAP_H__
# define __GMAP_H__

#include "GVector.hpp"
#include "GExport.h"

template<typename T, typename U>
class GEXPORTED GMap
{
	public:
		GMap(void);
		~GMap(void);
		unsigned int	Size(void) const;
		U				&operator[](const T &Key);
		void			PushBack(const T &Key, const U &Value);
		void			PushFront(const T &Key, const U &Value);
		void			Clear(void);
		bool			IsEmpty(void) const;
		bool			ExistKey(T Key);
		bool			ExistValue(U Value);
		void			EraseKey(T Key);
		void			EraseValue(U Value);
		void			Erase(unsigned int Index);
		int 			IndexOfValue(U Value);
		int				IndexOfKey(T Key);
		T				&FrontKey(void);
		U				&FrontValue(void);
		T				&BackKey(void);
		U				&BackValue(void);
		T				&Key(unsigned int Position);
		U				&Value(unsigned int Position);
		

	private:
		GVector<T>		_key;
		GVector<U>		_value;
};

template<typename T, typename U>
void	GMap<T, U>::PushBack(const T &t, const U &u)
{
	this->_key.PushBack(t);
	this->_value.PushBack(u);
}

template<typename T, typename U>
bool	GMap<T, U>::IsEmpty(void) const
{
	if (this->_key.Size() == 0)
		return (true);
	return (false);
}

template<typename T, typename U>
T		&GMap<T, U>::FrontKey(void)
{
	return (this->_key[0]);
}

template<typename T, typename U>
U		&GMap<T, U>::FrontValue(void)
{
	return (this->_value[0]);
}

template<typename T, typename U>
T		&GMap<T, U>::BackKey(void)
{
	return (this->_key[this->_key.Size() - 1]);
}

template<typename T, typename U>
U		&GMap<T, U>::BackValue(void)
{
	return (this->_value[this->_key.Size() - 1]);
}

template<typename T, typename U>
void	GMap<T, U>::Clear(void)
{
	this->_key.Clear();
	this->_value.Clear();
}
template<typename T, typename U>
void	GMap<T, U>::PushFront(const T &t, const U &u)
{
	this->_key.PushFront(t);
	this->_value.PushFront(u);
}	

template<typename T, typename U>
GMap<T, U>::GMap(void) : _key(), _value()
{

}

template<typename T, typename U>
GMap<T, U>::~GMap(void)
{
}

template<typename T, typename U>
unsigned int GMap<T, U>::Size(void) const
{
	return (this->_key.Size());
}

template<typename T, typename U>
U		&GMap<T, U>::operator[](const T &t)
{
	for (unsigned int i = 0; i < this->_key.Size(); ++i)
	{
		if (this->_key[i] == t)
			return (this->_value[i]);
	}
	this->PushBack(t, U());
	return (this->_value[this->Size() - 1]);
}

template<typename T, typename U>
bool	GMap<T, U>::ExistKey(T key)
{
	for (unsigned int i = 0; i < this->_key.Size(); ++i)
	{
		if (key == this->_key[i])
			return (true);
	}
	return (false);
}

template<typename T, typename U>
bool	GMap<T, U>::ExistValue(U value)
{
	for (unsigned int i = 0; i < this->_value.Size(); ++i)
	{
		if (value == this->_value[i])
			return (true);
	}
	return (false);
}

template<typename T, typename U>
void	GMap<T, U>::EraseValue(U value)
{
	int pos = this->_value.IndexOf(value);
	if (pos == -1)
		return ;
	this->_value.Erase(pos);
	this->_key.Erase(pos);
}

template<typename T, typename U>
int 	GMap<T, U>::IndexOfValue(U Value)
{
	return (this->_value.IndexOf(Value));
}

template<typename T, typename U>
int		GMap<T, U>::IndexOfKey(T Key)
{
	return (this->_key.IndexOf(Key));
}

template<typename T, typename U>
void	GMap<T, U>::EraseKey(T key)
{
	int pos = this->_key.IndexOf(key);
	if (pos == -1)
		return ;
	this->_value.Erase(pos);
	this->_key.Erase(pos);
}

template<typename T, typename U>
void	GMap<T, U>::Erase(unsigned int Index)
{
	if (Index < this->_key.Size())
	{
		this->_value.Erase(Index);
		this->_key.Erase(Index);
	}
}

template<typename T, typename U>
T		&GMap<T, U>::Key(unsigned int index)
{
	return (this->_key[index]);
}

template<typename T, typename U>
U		&GMap<T, U>::Value(unsigned int index)
{
	return (this->_value[index]);
}

#endif
