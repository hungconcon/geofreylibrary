using System;
using System.Collections.Generic;

namespace G
{
    public class GVector<T> : List<T>
    {
      
		public GVector()
        {

        }

        public GVector(T Elem)
        {
            this.Add(Elem);
        }

        public GVector(List<T> Vector)
        {
            UInt32 i = 0;
            while (i < Vector.Count)
            {
                this.Add(Vector[(Int32)i]);
                ++i;
            }
        }
        public void     PushFront(T Elem)
        {
            this.Insert(0, Elem);
        }
		public void     PushBack(T Elem)
        {
            this.Add(Elem);
        }
	    public void			Erase(UInt32 Position)
        {
            this.RemoveAt((Int32)Position);
        }
		public void			Delete(T Elem)
        {
            //this.RemoveAll(Elem);
        }
		public Boolean      IsEmpty()
        {
            if (this.Count == 0)
                return (true);
            return (false);
        }
        public T            PopFront()
        {
            T elem = this[0];
            this.RemoveAt(0);
            return (elem);
        }
		public T		PopBack()
        {
            T elem = this[this.Count - 1];
            this.RemoveAt(this.Count - 1);
            return (elem);
        }
		public T		Front()
        {
            return (this[0]);
        }
		public T	    Back()
        {
            return (this[this.Count - 1]);
        }
		public UInt32 Size
        {
            get
            { 
                return  ((UInt32)this.Count);
            }
        }
    }
}