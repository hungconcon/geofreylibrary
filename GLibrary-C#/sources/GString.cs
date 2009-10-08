using System;

namespace G
{
    public class GString
    {
        String  _str;
        
        [Flags]
        public enum CaseOption {CASE_SENSITIVE = 1, CASE_INSENSITIVE = 2};

        public GString()
        {
            this._str = "";      
        }
        public GString(String str)
        {
            this._str = str;
        }
        public GString(Char[] str)
        {
            this._str = str.ToString();
        }
        public GString(Boolean b)
        {
            this._str = b.ToString();
        }
        public GString(Char c)
        {
            this._str = c.ToString();
        }
        public GString(GString g)
        {
            this._str = g._str;
        }
        public GString(UInt32 nbr)
        {
            this._str = nbr.ToString();
        }
        public GString(UInt16 nbr)
        {
            this._str = nbr.ToString();
        }
        public GString(UInt64 nbr)
        {
            this._str = nbr.ToString();
        }
        public GString(Int64 nbr)
        {
            this._str = nbr.ToString();
        }
        public GString(Int32 nbr)
        {
            this._str = nbr.ToString();
        }
        public GString(Int16 nbr)
        {
            this._str = nbr.ToString();
        }
        public void         Clear()
        {
            this._str = "";
        }
        public GString      Substr(int StartIndex)
        {
            return new GString(this._str.Substring(StartIndex));
        }
        public GString      Substr(int StartIndex, int EndIndex)
        {
            return new GString(this._str.Substring(StartIndex, EndIndex - StartIndex));
        }
        public Boolean      IsEmpty()
        {
            if (this._str.Length == 0)
                return (true);
            return (false);
        }

        public Boolean      Contain(GString s, CaseOption op)
        {
            if (op == CaseOption.CASE_SENSITIVE)
                return (this._str.Contains(s._str));
            String news = this._str.ToLower();
            s = s._str.ToLower();
            return (this._str.Contains(s._str));
        }
        public GString Replace(GString Find, GString Rep, CaseOption op)
        {
            this._str.Replace(Find._str, Rep._str);
        }
        public Boolean      StartWith(GString str)
        {
            return (this._str.StartsWith(str._str));
        }

        public Boolean      EndWith(GString str)
        {
            return (this._str.EndsWith(str._str));
        }

        public Boolean      Compare(GString str)
        {
            return (this._str.CompareTo(str._str));
        }

        public int Size()
        {
            return (this._str.Length);
        }
        public GString ToUpper()
        {
            return (this._str.ToUpper());
        } 
        public GString ToLower()
        {
            return (this._str.ToLower());
        }
        public GString  Remove(Int32 StartIndex, Int32 Nbr)
        {
            return (this._str.Remove(StartIndex, Nbr));
        }
        public GString  RigthJustified(Int32 Nbr)
        {
            return (this._str.PadRight(Nbr, ' '));
        }
        public GString  RigthJustified(Int32 Nbr, Char c)
        {
            return (this._str.PadRight(Nbr, c));
        }
        public GString  LeftJustified(Int32 Nbr)
        {
            return (this._str.PadLeft(Nbr, ' '));
        }
        public GString  LeftJustified(Int32 Nbr, Char c)
        {
            return (this._str.PadLeft(Nbr, c));
        }
        public GString  Insert(Int32 StartIndex, GString str)
        {
            return (this._str.Insert(StartIndex, str._str));
        }
        public GString  LeftTrim()
        {
            return (this._str.TrimStart());
        }
        public GString  RigthTrim()
        {
            return (this._str.TrimEnd());
        }
        public  GString Trim()
        {
            return (this._str.Trim());
        }
        public int Length()
        {
            return (this._str.Length);
        }
        public Boolean  ToBool()
        {
            return (Convert.ToBoolean(this._str));
        }
        public String   ToString()
        {
            return(this._str);
        }
        public UInt32   ToUnsignedInt()
        {
            return (Convert.ToUInt32(this._str));
        }
        public UInt16   ToUnsignedShort()
        {
            return (Convert.ToUInt16(this._str));
        }
        public Int32    ToInt()
        {
            return (Convert.ToInt32(this._str));
        }
        public Int16    ToShort()
        {
            return (Convert.ToInt16(this._str));
        }
        public Double    ToDouble()
        {
            return (Convert.ToDouble(this._str));
        }
        public Char[]    ToChar()
        {
            return (this._str.ToCharArray());
        }
    }
}
