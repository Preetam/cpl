#pragma once

#include <stdexcept> // std::runtime_error

#include "socket.hpp"

namespace cpl
{
namespace net
{

class TCP_Socket : public Socket
{
public:
	inline void listen()
	{
		listen(128);
	}

	inline void listen(int backlog)
	{
		if (::listen(fd, backlog) < 0) {
			throw std::runtime_error("failed to listen on socket");
		}
	}

	inline void bind(std::string address, int port)
	{
		local_address = IP(address);
		local_port = port;

		fd = socket(local_address.family(), SOCK_STREAM, 0);
		if (fd < 0) {
			throw std::runtime_error("couldn't create socket");
		}

		struct sockaddr_storage addr;

		if (local_address.family() == AF_INET) {
			auto addr_in = reinterpret_cast<struct sockaddr_in*>(&addr);
			addr_in->sin_family = local_address.family();
			addr_in->sin_addr = local_address.addr.v4_addr;
			addr_in->sin_port = htons(port);
		} else {
			auto addr_in6 = reinterpret_cast<struct sockaddr_in6*>(&addr);
			addr_in6->sin6_family = local_address.family();
			addr_in6->sin6_addr = local_address.addr.v6_addr;
			addr_in6->sin6_port = htons(port);
		}

		if (::bind(fd, reinterpret_cast<struct sockaddr*>(&addr), sizeof addr) < 0) {
			throw std::runtime_error("failed to bind socket");
		}
	}

private:
	
}; // TCP_Socket

} // net
} // cpl
