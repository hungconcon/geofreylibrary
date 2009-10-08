
#ifndef __GSTREAM_H__
# define __GSTREAM_H__

#include "GString.h"
#include "GIStream.h"
#include "GOStream.h"
#include "GExport.h"

class GEXPORTED GStream : public GIStream, public GOStream
{	
	public:
		virtual ~GStream(void){};
};

#endif
