using System;
using System.Threading;

namespace G
{
    public class GThread
    {
        Thread  _th;
        Boolean _meth = false;
        Boolean _start = false;

        public GThread(ThreadStart Methode)
        {
            this._meth = true;
            this._th = new Thread(new ThreadStart(Methode));
        }

        public GThread()
        {

        }

        public void Start()
        {
            if (this._meth)
            {
                this._th.Start();
                this._start = true;
            }
        }

        public void Start(object Obj)
        {
            if (this._meth)
            {
                this._th.Start(Obj);
                this._start = true;
            }
        }

        public void Abort()
        {
            if (this._start == true)
            {
                this._th.Abort();
                this._th.Join();
            }
        }
        public void SetMethod(ParameterizedThreadStart Methode)
        {
            this._meth = true;
            this._th = new Thread(Methode);
        }
    }
}

