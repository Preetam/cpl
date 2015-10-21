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
	: fd(-1)
	{
	}

	TCP_Connection(int fd, SockAddr& remote)
	: fd(fd), remote(remote)
	{
	}

	TCP_Connection(TCP_Connection&& rhs) {
		if (fd >= 0) {
			close(fd);
		}
		fd = rhs.fd;
		remote = rhs.remote;
		rhs.fd = -1;
	}

	TCP_Connection& operator =(TCP_Connection&& rhs)
	{
		if (fd >= 0) {
			close(fd);
		}
		fd = rhs.fd;
		remote = rhs.remote;
		rhs.fd = -1;
		return *this;
	}

	// Disable copying.
	TCP_Connection(const TCP_Connection&) = delete;
	TCP_Connection& operator =(const TCP_Connection&) = delete;

	~TCP_Connection() throw()
	{
		if (fd >= 0) {
			close(fd);
		}
	}

	inline int
	connect(SockAddr& address)
	{
		fd = socket(address.ip.family, SOCK_STREAM, 0);
		if (fd < 0) {
			return -1;
		}
		struct sockaddr_storage addr;
		socklen_t size;
		if (address.ip.family == AF_INET) {
			auto addr_in = reinterpret_cast<struct sockaddr_in*>(&addr);
			addr_in->sin_family = address.ip.family;
			addr_in->sin_addr = address.ip.addr.v4;
			addr_in->sin_port = htons(address.port);
			size = sizeof(sockaddr_in);
		} else {
			auto addr_in6 = reinterpret_cast<struct sockaddr_in6*>(&addr);
			addr_in6->sin6_family = address.ip.family;
			addr_in6->sin6_addr = address.ip.addr.v6;
			addr_in6->sin6_port = htons(address.port);
			size = sizeof(sockaddr_in6);
		}
		if (::connect(fd, reinterpret_cast<struct sockaddr*>(&addr), size) < 0) {
			return -2;
		}
		return 0;
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

	inline SockAddr&
	remote_address() const
	{
		return remote;
	}
private:
	int fd;
	SockAddr remote;
}; // TCP_Connection

} // net
} // cpl
