#ifndef socket_hpp_
#define socket_hpp_

// C++
#include <string>
#include <stdexcept>

// socket
#include <sys/socket.h>

// close
#include <unistd.h>

// IP
#include "ip.hpp"

// SockAddr
#include "sockaddr.hpp"

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

#endif
