#pragma once

#include <mutex>

namespace custom_lock {
	
	template <class mutex> class lock_guard {
		public:
		    explicit lock_guard<mutex>(mutex& m):priv_mutex(m)  {
				priv_mutex.lock();
			}

			
			~lock_guard() {
				priv_mutex.unlock();
			}

			lock_guard(lock_guard const&) = delete;
			lock_guard& operator=(lock_guard const&) = delete;

		private:
			mutex&  priv_mutex;
	};



}