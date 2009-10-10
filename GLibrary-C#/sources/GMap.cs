using System;
using System.Collections.Generic;

namespace G
{
    public class GMap<T, U> : Dictionary<T, U>
    {

        public GMap()
        {

        }

        public UInt32 Size
        {
            get
            {
                return ((UInt32)this.Count);
            }
        }
        public Boolean IsEmpty()
        {
            if (this.Count == 0)
                return (true);
            return (false);
        }
    }
}