using System;

namespace G
{
    public class GString
    {
        String  _str;
        
        [Flags]
        public enum CaseOption {CASE_SENSITIVE = 1, CASE_INSENSITIVE = 2};
        public enum SplitOption {SKIP_EMPTY_PARTS = 1, KEEP_EMPTY_PARTS = 2};

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
            return (this._str.Replace(Find._str, Rep._str));
        }
        public GString Replace(GString Find, GString Rep)
        {
            return (new GString(this._str.Replace(Find._str.ToString(), Rep._str)));
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
            if (str._str == this._str)
                return (true);
            return (false);
        }

        public int Size
        {
            get
            {
                return (this._str.Length);
            }
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
        public GString Remove(GString Str)
        {
            return (this.Replace(Str, ""));
        }
        public GString  RightJustified(Int32 Nbr)
        {
            return (this._str.PadLeft(Nbr, ' '));
        }
        public GString  RightJustified(Int32 Nbr, Char c)
        {
            return (this._str.PadLeft(Nbr, c));
        }
        public GString  LeftJustified(Int32 Nbr)
        {
            return (this._str.PadRight(Nbr, ' '));
        }
        public GString  LeftJustified(Int32 Nbr, Char c)
        {
            return (this._str.PadRight(Nbr, c));
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
        public int Length
        {
            get
            {
                return (this._str.Length);
            }
        }
        public Boolean  ToBool()
        {
            return (Convert.ToBoolean(this._str));
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
        public static GString operator +(GString s1, GString s2)
        {
            GString s = new GString();
            s._str = s1._str + s2._str;
            return s;
        }
        public override string ToString()
        {
            return (this._str);

        }
        public static implicit operator String(GString s)
        {
            return (s._str);
        }
        public static implicit operator GString(String s)
        {
            return (new GString(s));
        }
        public Char this[UInt32 Index] 
        {
            get
            {
                return (this._str[(Int32)Index]);
            }
        }

        Int32  Find(GString f, CaseOption c)
        {
            if (c == G.GString.CaseOption.CASE_INSENSITIVE)
            {
                String temp = this._str;
                temp = temp.ToLower();
                String fin = f._str.ToLower();
                return (temp.IndexOf(fin));
            }
            return (this._str.IndexOf(f._str));
        }

        Int32 Find(GString f, Int32 Position, CaseOption c)
        {
            if (c == G.GString.CaseOption.CASE_INSENSITIVE)
            {
                String temp = this._str;
                temp = temp.ToLower();
                String fin = f._str.ToLower();
                return (temp.IndexOf(fin, (Int32)Position));
            }
            return (this._str.IndexOf(f._str, (Int32)Position));
        }

        Int32 Find(GString f)
        {
            return (this._str.IndexOf(f._str));
        }

        public GStringList  Split(GString f, SplitOption splitop , CaseOption caseop)
        {
	        GStringList	vect = new GStringList();
	        if (this.Find(f, caseop) == -1)
	        {
		        vect.PushBack(this);
		        return (vect);
	        }
	        int pos = 0, pos1 = 0, pos2 = 0;
	        while (true)
	        {
		        pos1 = pos;
		        pos = this.Find(f, pos, caseop);
		        if (pos == -1)
			        break;
		        pos2 = pos;
		        GString ne = this.Substr(pos1, pos2);
		        if ((splitop == GString.SplitOption.SKIP_EMPTY_PARTS && ne.Size != 0) || splitop == G.GString.SplitOption.KEEP_EMPTY_PARTS) 
			        vect.PushBack(ne);
		        pos += f.Size;
	        }
	        if (pos1 != 0)
	        {
		        GString ne = new GString (this.Substr(pos1, this.Size));
		        if ((splitop == G.GString.SplitOption.SKIP_EMPTY_PARTS && ne.Size != 0) || splitop == G.GString.SplitOption.KEEP_EMPTY_PARTS) 
				        vect.PushBack(ne);
	        }
	        return (vect);	
        }
        public GStringList Explode(GString f, SplitOption splitop, CaseOption caseop)
        {
            return (this.Split(f, splitop, caseop));
        }
        public GStringList Explode(GString f)
        {
            return (this.Split(f, G.GString.SplitOption.SKIP_EMPTY_PARTS, G.GString.CaseOption.CASE_SENSITIVE));
        }
        public GStringList Split(GString f)
        {
            return (this.Split(f, G.GString.SplitOption.SKIP_EMPTY_PARTS, G.GString.CaseOption.CASE_SENSITIVE));
        }
        public static implicit operator GString(Char value)
        {
            return new GString(value);
        }
        public static implicit operator GString(UInt32 value)
        {
            return new GString(value);
        }
        public static implicit operator GString(UInt16 value)
        {
            return new GString(value);
        }
        public static implicit operator GString(UInt64 value)
        {
            return new GString(value);
        }
        public static implicit operator GString(Int32 value)
        {
            return new GString(value);
        }
        public static implicit operator GString(Int16 value)
        {
            return new GString(value);
        }
        public static implicit operator GString(Int64 value)
        {
            return new GString(value);
        }
        public static Boolean operator== (GString t1, GString t2)
        {
            if (t1._str == t2._str)
                return (true);
            return (false);
        }
        public static Boolean operator !=(GString t1, GString t2)
        {
            if (t1._str != t2._str)
                return (true);
            return (false);
        }
        public override Boolean Equals(object obj)
        {
            if (obj == null || this.GetType() != obj.GetType()) return false;
            GString t = (GString)obj;
            if (this._str == t._str)
                return (true);
            return (false);
        }
        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
    }
}
