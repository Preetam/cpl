#pragma once

#include <unistd.h>     // close
#include <sys/socket.h> // socket
#include <fcntl.h> // fnctl

#include <string> // std::string

#include "ip.hpp"
#include "sockaddr.hpp"

namespace cpl
{
namespace net
{

class Socket
{
public:
	Socket()
	: fd(-1)
	{
	}

	~Socket() throw()
	{
		if (fd >= 0) {
			close(fd);
		}
	}

	virtual int bind(std::string address, int port) throw() = 0;

	inline void
	set_nonblocking()
	{
		fcntl(fd, F_SETFL, SO_SNDTIMEO);
	}

	// Disable copying.
	Socket(const Socket&) = delete;
	Socket& operator =(const Socket&) = delete;

protected:
	int fd;
	SockAddr local_address;
}; // Socket

} // net
} // cpl
