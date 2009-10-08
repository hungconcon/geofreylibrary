
#include "GRandom.h"

unsigned int	GRandom(void)
{
	srand((int)time(NULL));
	return (rand());
}

unsigned int	GRandom(unsigned int min, unsigned int max)
{
	unsigned int	r(GRandom());
	while (r < min)
		r = GRandom();
	return (r % max);
}
