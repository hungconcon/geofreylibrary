
#include "GVolumeInformations.h"

GVolumeInformations::GVolumeInformations(const GString &Volume)
{
	char pathname[1024];
	GetVolumePathNamesForVolumeName(Volume.ToLPCSTR(), pathname, 1024, NULL);
	this->_path = pathname;
	
	//GetVolumeInformation(Volume.ToLPCSTR(), volumename, 1024, NULL, NULL, NULL, systemname, 1024);
}

GVolumeInformations::~GVolumeInformations(void)
{

}

GString	GVolumeInformations::GetPath(void) const
{
	return (this->_path);
}

bool	GVolumeInformations::IsHardDisk(void) const
{
	if (GetDriveType(this->_path.ToLPCSTR()) == DRIVE_FIXED)
		return (true);
	return (false);
}

bool	GVolumeInformations::IsCdRom(void) const
{
	if (GetDriveType(this->_path.ToLPCSTR()) == DRIVE_CDROM)
		return (true);
	return (false);
}

bool	GVolumeInformations::IsRemovableMedia(void) const
{
	if (GetDriveType(this->_path.ToLPCSTR()) == DRIVE_REMOVABLE)
		return (true);
	return (false);
}

bool	GVolumeInformations::SetLabel(const GString &Name) const
{
	if (SetVolumeLabel(this->_path.ToLPCSTR(), Name.ToLPCSTR()) == 0)
		return (false);
	return (true);
}

bool	GVolumeInformations::DeleteLabel(void) const
{
	if (SetVolumeLabel(this->_path.ToLPCSTR(), NULL) == 0)
		return (false);
	return (true);
}

long long	GVolumeInformations::TotalSpace(void) const
{
	long long test;
	if (GetDiskFreeSpaceEx(this->_path.ToLPCSTR(), NULL, (PULARGE_INTEGER)&test, NULL) == 0)
		return (0);
	return (test);

}

long long	GVolumeInformations::FreeSpace(void) const
{
	long long test;
	if (GetDiskFreeSpaceEx(this->_path.ToLPCSTR(), NULL, NULL, (PULARGE_INTEGER)&test) == 0)
		return (0);
	return (test);
}








