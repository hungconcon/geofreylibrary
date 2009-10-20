
#ifndef		__GPAIR_HPP__
# define	__GPAIR_HPP__

template<class T, class U>
class	GPair
{
public:
	GPair(const T &k, const U &v) : _key(k), _value(v)
	{
	}
	T	&GetKey(void)
	{
		return (this->_key);
	}
	U	&GetValue(void)
	{
		return (this->_value);
	}

private:
	T	_key;
	U	_value;
};

#endif

