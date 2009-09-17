
#include "GIntegerList.h"

GIntegerList::GIntegerList(unsigned int n) : GVector<int>(n) 
{

}

GIntegerList::~GIntegerList(void)
{

}

void	GIntegerList::Sort(OrderOption order)
{
	bool test = true;
	while (test)
	{
		test = false;
		for (unsigned int i = 1; i < this->Size(); ++i)
		{
			if (order == GIntegerList::ORDER_ASC)
			{
				if (this->_tab[i] < this->_tab[i - 1])
				{
					test = true;
					int cur = this->_tab[i];
					this->_tab[i] = this->_tab[i - 1];
					this->_tab[i - 1] = cur;
				}
			}
			else if (order == GIntegerList::ORDER_DESC)
			{
				if (this->_tab[i] > this->_tab[i - 1])
				{
					test = true;
					int cur = this->_tab[i];
					this->_tab[i] = this->_tab[i - 1];
					this->_tab[i - 1] = cur;
				}
			}
		}
	}
}

int		GIntegerList::Sum(void) const
{
	int sum = 0;
	for (unsigned int i = 0; i < this->Size(); ++i)
		sum += this->_tab[i];
	return (sum);
}

float	GIntegerList::Average(void) const
{
	float av;
	av = (float)(this->Sum() / this->Size());
	return (av);
}
