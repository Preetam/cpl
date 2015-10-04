// This is a reader/writer mutual exclusion lock implementation
// based on Go's RWMutex, which is available at
// https://golang.org/src/sync/rwmutex.go.
#pragma once

#include <atomic>
#include <stdexcept>

#include "semaphore.hpp"
#include "mutex.hpp"

namespace cpl
{

const int32_t max_readers = 1 << 30;

class RWMutex
{
public:
	RWMutex()
	: _r_sem(0), _w_sem(0), r_count(0), r_wait(0)
	{
	}

	inline void
	r_lock()
	{
		// Increment the reader count. If it's still negative,
		// there is an active writer.
		if ((++r_count) < 0) {
			// There is an active writer, so wait for it.
			_r_sem.acquire();
		}
	}

	inline void
	r_unlock()
	{
		// Decrement the reader count.
		int32_t r = --r_count;
		if (r < 0) {
			if (r+1 == 0 || r+1 == -max_readers) {
				throw std::runtime_error("r_unlock of unlocked RWMutex");
			}
			// Decrement the number of readers a writer is waiting on.
			if ((--r_wait) == 0) {
				// There is a waiting writer and this is the last
				// reader, so we can signal the writer to continue.
				_w_sem.release();
			}
		}
	}

	inline void
	lock()
	{
		// Lock for writing.
		_mu.lock();
		// Announce to readers that there is a pending writer.
		int32_t r = (r_count -= max_readers) + max_readers;
		if (r != 0 && (r_wait += r) != 0) {
			// Wait for the readers.
			_w_sem.acquire();
		}
	}

	inline void
	unlock()
	{
		// Announce to readers that there is no active writer.
		int32_t r = (r_count += max_readers);
		if (r >= max_readers) {
			throw std::runtime_error("unlock of unlocked RWMutex");
		}
		// Unblock blocked readers.
		for (int i = 0; i < r; i++) {
			_r_sem.release();
		}
		// Unlock for writing.
		_mu.unlock();
	}

private:
	Mutex _mu;
	Semaphore _r_sem;
	Semaphore _w_sem;
	std::atomic<int32_t> r_count;
	std::atomic<int32_t> r_wait;

}; // RWMutex

} // cpl
