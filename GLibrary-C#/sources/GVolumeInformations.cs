using System;
using System.IO;

namespace G
{
    public class GVolumeInformations
    {
        GString _path;


        public GVolumeInformations(GString Volume)
        {
            this._path = Volume;
        }

        public GString GetPath()
        {
            return (this._path);
        }
        public Boolean IsHardDisk()
        {
            DriveInfo monDriveInfo = new DriveInfo(this._path);
            if (monDriveInfo.DriveType == DriveType.Fixed)
                return (true);
            return (false);
        }

        public Boolean IsCdRom()
        {
            DriveInfo monDriveInfo = new DriveInfo(this._path);
            if (monDriveInfo.DriveType == DriveType.CDRom)
                return (true);
            return (false);
        }

        public Boolean IsRemovableMedia()
        {
            DriveInfo monDriveInfo = new DriveInfo(this._path);
            if (monDriveInfo.DriveType == DriveType.Removable)
                return (true);
            return (false);
        }

        /*

bool	GVolumeInformations::SetLabel(GString Name) 
{
	if (SetVolumeLabel(this->_path.ToLPCSTR(), Name.ToLPCSTR()) == 0)
		return (false);
	return (true);
}

bool	GVolumeInformations::DeleteLabel(void) 
{
	if (SetVolumeLabel(this->_path.ToLPCSTR(), NULL) == 0)
		return (false);
	return (true);
}

long long	GVolumeInformations::TotalSpace(void) 
{
	long long test;
	if (GetDiskFreeSpaceEx(this->_path.ToLPCSTR(), NULL, (PULARGE_INTEGER)test, NULL) == 0)
		return (0);
	return (test);

}

long long	GVolumeInformations::FreeSpace(void) 
{
	long long test;
	if (GetDiskFreeSpaceEx(this->_path.ToLPCSTR(), NULL, NULL, (PULARGE_INTEGER)test) == 0)
		return (0);
	return (test);
}
        */
    }
}







