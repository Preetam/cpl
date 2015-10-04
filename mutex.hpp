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
		_m.lock();
	}

	void
	unlock()
	{
		_m.unlock();
	}

private:
	std::mutex _m;
}; // Mutex

} // cpl