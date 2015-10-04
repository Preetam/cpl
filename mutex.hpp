#pragma once

#include <mutex>

namespace cpl
{

class Mutex
{
public:
	void
	lock()
	{
		m.lock();
	}

	void
	unlock()
	{
		m.unlock();
	}

private:
	std::mutex m;
}; // Mutex

} // cpl