
#ifndef __GOUT_H__
# define __GOUT_H__

#include "GOStream.h"
#include "GString.h"
//#include <unistd.h>
#include <io.h>


class GOut : public GOStream
{
	public:
		GOut(void);
		~GOut(void);
		void	Write(const GString &);
		void	WriteLine(const GString &);
		
		void	operator<<(const GString &);

	private:
		static GString	_out;
};

#endif
