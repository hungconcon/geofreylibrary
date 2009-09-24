
#ifndef __GSINGLETON_H__
# define __GSINGLETON_H__

#include "GExport.h"

template<typename T>
class GEXPORTED GSingleton
{
	public:
		static T *GetInstance(void);

	private:
		T	*_instance;
};

template<typename T>
T *GSingleton<T>::_instance = NULL;

static T *GetInstance(void);

template<typename T>
GSingleton<T>::GSingleton(void)
{

}

GSingleton<T>::~GSingleton(void)
{

}

template<typename T>
T	*GSingleton<T>::GetInstance(void)
{
	if (_singleton == NULL)
		_singleton = new T();
	return (_singleton);
}

template<typename T>
void	GSingleton<T>::DeleteInstance(void)
{
	if (_singleton)
	{
		delete _singeton;
		_singleton = NULL;
	}
}

#endif