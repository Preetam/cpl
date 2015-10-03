#include <mutex>
#include <condition_variable>

namespace cpl
{
class Semaphore {
public:
    Semaphore(int n)
    : _n(n)
    {
    }

    inline
    void acquire()
    {
        std::unique_lock<std::mutex> _(_m);
        _cv.wait(_, [this]() { return _n > 0; });
        _n--;
    }

    inline
    void release()
    {
        std::unique_lock<std::mutex> _(_m);
        _n++;
        _cv.notify_one();
    }

    // Disable copying.
    Semaphore(const Semaphore&) = delete;
    Semaphore& operator =(const Semaphore&) = delete;

private:
    int _n;
    std::mutex _m;
    std::condition_variable _cv;

}; // Semaphore
} // cpl
