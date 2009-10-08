using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace G
{
    public class GString
    {
        string  _str;

        public GString()
        {
            this._str = "";      
        }

        public GString(string str)
        {
            this._str = str;
        }

        public GString      Substr(int StartIndex)
        {
            return new GString(this._str.Substring(StartIndex));
        }

        public GString Substr(int StartIndex, int EndIndex)
        {
            return new GString(this._str.Substring(StartIndex, EndIndex - StartIndex));
        }

    }
}
