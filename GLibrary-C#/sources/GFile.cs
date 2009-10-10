using System;
using System.IO;
namespace G
{
    public class GFile
    {
        Boolean _open = true;
        GString _file;

        public GFile(GString file)
        {
            this._open = false;
            this._file = file;
        }
        public GFile()
        {
            this._open = false;
        }
        ~GFile()
        {
            this.Close();
        }
        public static bool Touch(GString FileName)
        {
            Boolean test = true;
            try
            {
                File.Create(FileName);
            }
            catch
            {
                test = false;
            }
            return (test);
        }
        public void SetFile(GString file)
        {
            this.Close();
            this._file = file;
        }
        public GString GetName()
        {
            return (this._file);
        }
        public static Boolean Rm(GString f)
        {
            return (true);
        }
        public Boolean Rm()
        {
            return (true);
        }
        public Boolean Create()
        {
            return (true);
        }
        public void Open(Boolean Binary)
        {

        }
        public void Clear()
        {

        }
        public void Close()
        {

        }
        public void Read()
        {

        }
        public GString Read(UInt32 Size)
        {
            return (new GString());
        }
        public void Write(GString ToWrite)
        {

        }
        public Boolean IsOpen()
        {
            return (this._open);
        }
        public void GoToBegin()
        {

        }
        public void GoToEnd()
        {
        }
        public void GoTo(UInt32 Posistion)
        {

        }
        public UInt32 CurrentIndex()
        {
            return (1);
        }
        public Boolean EndOfFile()
        {
            return (true);
        }
    }
}