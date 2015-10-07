#pragma once

#include <mutex>
#include <condition_variable>

namespace cpl
{
class Semaphore {
public:
	Semaphore()
	: n(0)
	{
	}

	Semaphore(int n)
	: n(n)
	{
	}

	inline
	void acquire()
	{
		std::unique_lock<std::mutex> lk(m);
		cv.wait(lk, [this]() { return n > 0; });
		n--;
	}

	inline
	void release()
	{
		std::unique_lock<std::mutex> lk(m);
		n++;
		cv.notify_one();
	}

	// Disable copying.
	Semaphore(const Semaphore&) = delete;
	Semaphore& operator =(const Semaphore&) = delete;

private:
	int n;
	std::mutex m;
	std::condition_variable cv;

}; // Semaphore
} // cpl
