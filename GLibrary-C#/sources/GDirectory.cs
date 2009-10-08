using System;
using System.IO;

namespace G
{
    public class GDirectory
    {
        private GString     _directory;

        public              GDirectory()
        {
	        this._directory = GetCurrentDirectory();
        }
        /*public GFileInfos[] Ls()
        {
            String[] files;
            files = Directory.GetFileSystemEntries(this._directory);
            int filecount = files.GetUpperBound(0) + 1;
            GFileInfos[] list = new GFileInfos[filecount];
            int i = 0;
            while (i < filecount)
            {
                list[i] = files[i];
                ++i;
            }
            return (list);
        }
        public static GFileInfos[] Ls(GString Directory)
        {
            GFileInfos[] list;
            String[] files;
            files = Directory.GetFileSystemEntries(Directory);
            int filecount = files.GetUpperBound(0) + 1;
            int i = 0;
            while (i < filecount)
            {
                list[i] = files[i];
                ++i;
            }
            return (list);
        }*/
        public bool         Mkdir(GString Dir)
        {
            bool test = true;
            try
            {
                Directory.CreateDirectory(System.IO.Path.Combine(this._directory.ToString(), DirToString()));
            }
            catch
            {
                test = false;
            }
            return (test);
        }
        public bool		    Mkpath(GString Path)
        {
            bool test = true;
            try
            {
                Directory.CreateDirectory(System.IO.Path.Combine(this._directory.ToString(), Path.ToString()));
            }
            catch
            {
                test = false;
            }
            return (test);
        }
        public static bool  Rename(GString f1, GString f2)
        {
            test = true;
            try
            {
                Directory.Move(f1.ToString(), f2.ToString());
            }
            catch
            {
                test = false;
            }
            return (test);
        }
        public GString      Pwd()
        {
            return (this._directory);
        }
        public bool         Cd(GString Dir)
        {
            bool test = true;
            try
            {
                Directory.SetCurrentDirectory(Dir.ToString());
                this._directory = Directory.GetCurrentDirectory();
            }
            catch
            {
                test = false;
            }
            return (test);
        }
        public Boolean      Rmdir(bool Recursif)
        {
            Boolean test = true;
            try
            {
                Directory.Delete(this._directory.ToString(), Recursif);
                this._directory = Directory.GetCurrentDirectory();
            }
            catch
            {
                test = false;
            }
            return (test);
        }
        public static Boolean  Rmdir(GString Dir, bool Recursif)
        {
            Boolean test = true;
            try
            {
                Directory.Delete(Dir.ToString(), Recursif);
                this._directory = Directory.GetCurrentDirectory();
            }
            catch
            {
                test = false;
            }
            return (test);
        }
        public bool         Rmpath(GString Path)
        {
	        return (true);	
        }

/*        
static void PrintSpecFolder()
{
    // Répertoire spéciaux
    Console.WriteLine("Répertoire spéciaux");
    Environment.SpecialFolder[] sfe = (Environment.SpecialFolder[]) 
                                      Enum.GetValues(typeof(Environment.SpecialFolder));
    for (int i = 0; i<sfe.Length; i++)
        Console.WriteLine(Environment.GetFolderPath(sfe[i]));
}

GString		GDirectory::GetPathDesktop(void)
{
#if defined (GWIN)
	GRegistry r;
	r.OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
	GString t(r.ReadStringValue("Desktop"));
	r.CloseKey();
	return (t);
#else
	return ("");
#endif
}

GString		GDirectory::GetPathFonts(void)
{
#if defined (GWIN)
	GRegistry r;
	r.OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
	GString t(r.ReadStringValue("Fonts"));
	r.CloseKey();
	return (t);
#else
	return ("");
#endif
}

GString		GDirectory::GetPathMusic(void)
{
#if defined (GWIN)
	GRegistry r;
	r.OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
	GString t(r.ReadStringValue("My Music"));
	r.CloseKey();
	return (t);
#else
	return ("");
#endif
}
GString		GDirectory::GetPathVideos(void)
{
#if defined (GWIN)
	GRegistry r;
	r.OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
	GString t(r.ReadStringValue("My Video"));
	r.CloseKey();
	return (t);
#else
	return ("");
#endif
}
GString		GDirectory::GetPathPictures(void)
{
#if defined (GWIN)
	GRegistry r;
	r.OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
	GString t(r.ReadStringValue("My Pictures"));
	r.CloseKey();
	return (t);
#else
	return ("");
#endif
}
GString		GDirectory::GetPathCookies(void)
{
#if defined (GWIN)
	GRegistry r;
	r.OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
	GString t(r.ReadStringValue("Cookies"));
	r.CloseKey();
	return (t);
#else
	return ("");
#endif
}
GString		GDirectory::GetPathDocuments(void)
{
#if defined (GWIN)
	GRegistry r;
	r.OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
	GString t(r.ReadStringValue("Personal"));
	r.CloseKey();
	return (t);
#else
	return ("");
#endif
}
GString		GDirectory::GetPathHistory(void)
{
#if defined (GWIN)
	GRegistry r;
	r.OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
	GString t(r.ReadStringValue("History"));
	r.CloseKey();
	return (t);
#else
	return ("");
#endif
}
GString		GDirectory::GetPathStartMenu(void)
{
#if defined (GWIN)
	GRegistry r;
	r.OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
	GString t(r.ReadStringValue("Start Menu"));
	r.CloseKey();
	return (t);
#else
	return ("");
#endif
}
GString		GDirectory::GetPathProgramsMenu(void)
{
#if defined (GWIN)
	GRegistry r;
	r.OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
	GString t(r.ReadStringValue("Programs"));
	r.CloseKey();
	return (t);
#else
	return ("");
#endif
}
GString		GDirectory::GetPathFavorites(void)
{
#if defined (GWIN)
	GRegistry r;
	r.OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
	GString t(r.ReadStringValue("Favorites"));
	r.CloseKey();
	return (t);
#else
	return ("");
#endif
}
GString		GDirectory::GetPathRoot(void)
{
#if defined (GWIN)
	const unsigned long BUFSIZE = 255;
	unsigned long dwSize = BUFSIZE;
	char pbuf[ BUFSIZE + 1];
	::GetWindowsDirectory(pbuf, dwSize);
	return (pbuf);
#else
	return ("");
#endif
}*/


    }
}