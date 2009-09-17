
#ifndef __GFILE_H__
# define __GFILE_H__

#include "GStream.h"
#include "GString.h"
#include "GExport.h"

class GEXPORTED GFile : public GStream
{
	public:
		GFile(const GString &);
		GFile(void);
		~GFile(void);

		static bool		Rm(const GString &);
		bool			Rm(void);
		void			GoToEnd(void);
		void			GoToBegin(void);
		void			GoTo(unsigned int);
		bool			EndOfFile(void);
		bool			IsOpen(void) const;
		void			Open(bool Binary = false);
		void			Close(void);
		void			Write(const GString &);
		GString			Read(void);
		GString			Read(unsigned int);
		void			Read(void *, unsigned int Size);
		static bool		Create(const GString &);
		long			CurrentIndex(void);
		void			SetFile(const GString &);
		void			Clear(void);
		GString			GetName(void);
		
		//void			Touch(void);

	private:
		GString		_file;
		FILE		*_pFile;
		bool		_open;
		GString		_mode;
};

#endif
