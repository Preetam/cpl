#pragma once

#include <unistd.h>     // close
#include <sys/socket.h> // socket

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

	virtual void bind(std::string address, int port) = 0;

protected:
	int fd;
	SockAddr local_address;
}; // Socket

} // net
} // cpl
