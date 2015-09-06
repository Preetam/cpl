#pragma once

#include "sys/socket.h"
#include "sys/time.h"

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
	: _fd(fd), _local(local), _remote(remote)
	{
	}

	TCP_Connection& operator = (TCP_Connection&& rhs)
	{
		_fd = rhs._fd;
		_local = rhs._local;
		_remote = rhs._remote;
		rhs._fd = -1;
		return *this;
	}

	~TCP_Connection()
	{
		close(_fd);
	}

	inline void
	set_timeout(uint seconds, uint microseconds)
	{
		struct timeval tval;
		tval.tv_sec = seconds;
		tval.tv_usec = microseconds;
		setsockopt(_fd, SOL_SOCKET, SO_RCVTIMEO, &tval, sizeof(tval));
		setsockopt(_fd, SOL_SOCKET, SO_SNDTIMEO, &tval, sizeof(tval));
	}

	inline int
	recv(const void* buf, size_t len, int flags)
	{
		auto ret = (int)(::recv(_fd, const_cast<void*>(buf), len, flags));
		return ret;
	}

	inline int
	send(const void* buf, size_t len, int flags)
	{
		auto ret = (int)(::send(_fd, const_cast<void*>(buf), len, flags));
		return ret;
	}

	inline SockAddr
	local_address()
	{
		return _local;
	}

	inline SockAddr
	remote_address()
	{
		return _remote;
	}

private:
	int _fd;
	SockAddr _local;
	SockAddr _remote;

	TCP_Connection(const TCP_Connection&);
	TCP_Connection& operator = (const TCP_Connection&);
};

} // net
} // cpl
