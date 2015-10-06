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

protected:
	int fd;
	SockAddr local_address;

private:
	Socket(const Socket&);
	Socket& operator = (const Socket&);
}; // Socket

} // net
} // cpl
