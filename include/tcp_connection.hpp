#pragma once

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

	TCP_Connection(int fd, SockAddr local_address, SockAddr remote_address)
	: fd(fd), local(local_address), remote(remote_address)
	{
	}

	TCP_Connection& operator = (TCP_Connection&& rhs)
	{
		fd = rhs.fd;
		local = rhs.local;
		remote = rhs.remote;
		rhs.fd = -1;
		return *this;
	}

	~TCP_Connection()
	{
		close(fd);
	}

	inline int recv(const void* buf, size_t len, int flags)
	{
		auto ret = (int)(::recv(fd, const_cast<void*>(buf), len, flags));
		return ret;
	}

	inline int send(const void* buf, size_t len, int flags)
	{
		auto ret = (int)(::send(fd, const_cast<void*>(buf), len, flags));
		return ret;
	}

	inline SockAddr local_address()
	{
		return local;
	}

	inline SockAddr remote_address()
	{
		return remote;
	}

private:
	int fd;
	SockAddr local;
	SockAddr remote;

	TCP_Connection(const TCP_Connection&);
	TCP_Connection& operator = (const TCP_Connection&);
};

} // net
} // cpl
