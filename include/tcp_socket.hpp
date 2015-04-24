#ifndef tcp_socket_hpp_
#define tcp_socket_hpp_

#include <socket.hpp>

#include <stdexcept>

namespace cpl
{
namespace net
{

class TCP_Socket : public Socket
{
public:
	void listen()
	{
		listen(128);
	}

	void listen(int backlog)
	{
		if (::listen(fd, backlog) < 0) {
			throw std::runtime_error("failed to listen on socket");
		}
	}

private:
	
}; // TCP_Socket

} // net
} // cpl

#endif
