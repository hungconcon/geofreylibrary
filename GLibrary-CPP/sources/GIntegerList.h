
#ifndef __GINTEGER_H__
# define __GINTEGER_H__

#include "GVector.hpp"

class GIntegerList : public GVector<int>
{
	public:
		enum OrderOption
		{
			ORDER_ASC,
			ORDER_DESC
		};
		GIntegerList(unsigned int n = 10);
		~GIntegerList(void);
	
		void	Sort(OrderOption = GIntegerList::ORDER_ASC);
		int		Sum(void) const;
					float	Average(void) const;
};

#endif
