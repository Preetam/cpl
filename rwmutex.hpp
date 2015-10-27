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
	: r_sem(0), w_sem(0), r_count(0), r_wait(0)
	{
	}

	inline void
	r_lock()
	{
		// Increment the reader count. If it's still negative,
		// there is an active writer.
		if ((++r_count) < 0) {
			// There is an active writer, so wait for it.
			r_sem.acquire();
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
				w_sem.release();
			}
		}
	}

	inline void
	lock()
	{
		// Lock for writing.
		mu.lock();
		// Announce to readers that there is a pending writer.
		int32_t r = (r_count -= max_readers) + max_readers;
		if (r != 0 && (r_wait += r) != 0) {
			// Wait for the readers.
			w_sem.acquire();
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
			r_sem.release();
		}
		// Unlock for writing.
		mu.unlock();
	}

private:
	Mutex mu;
	Semaphore r_sem;
	Semaphore w_sem;
	std::atomic<int32_t> r_count;
	std::atomic<int32_t> r_wait;

}; // RWMutex

class RWLock
{
public:
	RWLock(RWMutex& mu, bool reader)
	: mu(mu), reader(reader)
	{
		if (reader) {
			mu.r_lock();
		} else {
			mu.lock();
		}
	}

	~RWLock()
	{
		if (reader) {
			mu.r_unlock();
		} else {
			mu.unlock();
		}
	}
private:
	bool reader;
	RWMutex& mu;
}; // RWLock

} // cpl
