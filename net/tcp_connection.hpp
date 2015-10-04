#pragma once

#include "sys/socket.h"
#include "sys/time.h"
#include "unistd.h"

#include "sockaddr.hpp"

namespace cpl
{
namespace net
{

class TCP_Connection
{
public:
	TCP_Connection()
	{
	}

	TCP_Connection(int fd, SockAddr local, SockAddr remote)
	: fd(fd), local(local), remote(remote)
	{
	}

	TCP_Connection(TCP_Connection&& rhs) {
		fd = rhs.fd;
		local = rhs.local;
		remote = rhs.remote;
		rhs.fd = -1;
	}

	TCP_Connection& operator =(TCP_Connection&& rhs)
	{
		fd = rhs.fd;
		local = rhs.local;
		remote = rhs.remote;
		rhs.fd = -1;
		return *this;
	}

	// Disable copying.
	TCP_Connection(const TCP_Connection&) = delete;
	TCP_Connection& operator =(const TCP_Connection&) = delete;

	~TCP_Connection() throw()
	{
		if (fd > 0) {
			close(fd);
		}
	}

	inline void
	set_timeout(uint seconds, uint microseconds)
	{
		struct timeval tval;
		tval.tv_sec = seconds;
		tval.tv_usec = microseconds;
		setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tval, sizeof(tval));
		setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &tval, sizeof(tval));
	}

	inline int
	recv(const void* buf, size_t len, int flags) const
	{
		auto ret = (int)(::recv(fd, const_cast<void*>(buf), len, flags));
		return ret;
	}

	inline int
	send(const void* buf, size_t len, int flags) const
	{
		auto ret = (int)(::send(fd, const_cast<void*>(buf), len, flags));
		return ret;
	}

	inline SockAddr
	local_address() const
	{
		return local;
	}

	inline SockAddr
	remote_address() const
	{
		return remote;
	}
private:
	int fd;
	SockAddr local;
	SockAddr remote;
}; // TCP_Connection

} // net
} // cpl
