using System;
using System.Threading;

namespace G
{
    public class GMutex
    {
        Mutex _mutex;
        bool _lock = false;

        public GMutex()
        {
            this._mutex = new Mutex();
        }

        public void Lock()
        {
            if (!this._lock)
            {
                this._mutex.WaitOne();
                this._lock = true;
            }
        }

        public void Unlock()
        {
            if (this._lock)
            {
                try
                {
                    this._mutex.ReleaseMutex();
                    this._lock = false;
                }
                catch
                {

                }
            }
        }

        public void Trylock()
        {
            if (!this._lock)
            {
                if (this._mutex.WaitOne(0))
                    this._lock = true;
            }
        }
        public Boolean IsLock()
        {
            return (this._lock);
        }
    }
}