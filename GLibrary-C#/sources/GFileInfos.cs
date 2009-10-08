using System;
using System.IO;

namespace G
{
    class GFileInfos
    {
        GString _file;

        public GFileInfos()
        {

        }
        public GFileInfos(GString file)
        {
            this._file = file;
        }
        public GFileInfos(GString Dir, GString File)
        {
            this._file = System.IO.Path.Combine(Dir.ToString(), File.ToString());
        }
        public GString FileName()
        {
            return (System.IO.Path.GetFileName(this._file.ToString()));
        }
        public static bool IsDirectory(GString Dir)
        {
            if (Directory.Exists(Dir.ToString()))
                return (true);
            return (false);
        }
        public bool IsDir()
        {
            if (Directory.Exists(this._file.ToString()))
                return (true);
            return (false);
        }
        public void SetFile(GString FileOrDirectory)
        {
            this._file = FileOrDirectory;
        }
        public Int64 Size()
        {
            try
            {
                System.IO.FileInfo monfichier = new System.IO.FileInfo(this._file.ToString());
                return (monfichier.Length);
            }
            catch
            {

            }
            return (-1);
        }
        public GDateTime BirthTime()
        {
            try
            {
                System.IO.FileInfo file = new System.IO.FileInfo(this._file.ToString());
                return (new GDateTime(file.CreationTime));
            }
            catch
            {

            }
            return (new GDateTime());
        }

        public GDateTime LastModificationTime()
        {
            try
            {
                System.IO.FileInfo file = new System.IO.FileInfo(this._file.ToString());
                return (new GDateTime(file.LastWriteTime));
            }
            catch
            {

            }
            return (new GDateTime());
        }
        public GDateTime LastAccessTime()
        {
            try
            {
                System.IO.FileInfo file = new System.IO.FileInfo(this._file.ToString());
                return (new GDateTime(file.LastAccessTime));
            }
            catch
            {

            }
            return (new GDateTime());
        }
        public bool Exist()
        {
            return (Directory.Exists(this._file.ToString()));
        }
    }
}