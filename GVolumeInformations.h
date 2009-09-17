
#ifndef __GVOLUMEINFORMATIONS_H__
# define __GVOLUMEINFORMATIONS_H__

#include <iostream>
#include "GExport.h"
#include "GString.h"

class GEXPORTED GVolumeInformations
{	
	public:
		GVolumeInformations(const GString &Volume);
		GVolumeInformations(void);
		~GVolumeInformations(void);

		GString		GetPath(void) const;
		bool		IsHardDisk(void) const;
		bool		IsCdRom(void) const;
		bool		IsRemovableMedia(void) const;
		bool		SetLabel(const GString &Name) const;
		long long	FreeSpace(void) const;
		bool		DeleteLabel(void) const;
		long long	TotalSpace(void) const;



	private:
		GString		_path;
};


#endif