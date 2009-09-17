
#ifndef __GCRYPTOGRAPHY_H__
# define __GCRYPTOGRAPHY_H__

#include "GString.h"
#include "GExport.h"

namespace GCryptography
{
	class GEXPORTED GBase64
	{
		public:
			static GString			Encode(const GString &);
			static GString			Decode(const GString &);

		private:
			static char				Encode64(unsigned char);
			static unsigned char	Decode64(char);
			static bool				IsBase64(char c);
	};


}

#endif

