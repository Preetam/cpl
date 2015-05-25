#pragma once

#include <unistd.h>     // close
#include <sys/socket.h> // socket

#include <string> // std::string

#include "ip.hpp"

namespace cpl
{
namespace net
{

class Socket
{
public:
	virtual void bind(std::string address, int port) = 0;

protected:
	int fd;
	IP local_address;
	int local_port;

}; // Socket

} // net
} // cpl
