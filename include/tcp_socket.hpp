#pragma once

#include <stdexcept> // std::runtime_error
#include <memory>

#include "socket.hpp"
#include "sockaddr.hpp"
#include "tcp_connection.hpp"

namespace cpl
{
namespace net
{

class TCP_Socket : public Socket
{
public:
	inline void
	listen()
	{
		listen(128);
	}

	inline void
	listen(int backlog)
	{
		if (::listen(fd, backlog) < 0) {
			throw std::runtime_error("failed to listen on socket");
		}
	}

	inline int
	bind(std::string ip, int port) throw()
	{
		local_address = SockAddr(IP(ip), port);
		fd = socket(local_address.ip.family, SOCK_STREAM, 0);
		if (fd < 0) {
			return -1;
		}
		struct sockaddr_storage addr;
		socklen_t size;
		if (local_address.ip.family == AF_INET) {
			auto addr_in = reinterpret_cast<struct sockaddr_in*>(&addr);
			addr_in->sin_family = local_address.ip.family;
			addr_in->sin_addr = local_address.ip.addr.v4;
			addr_in->sin_port = htons(port);
			size = sizeof(sockaddr_in);
		} else {
			auto addr_in6 = reinterpret_cast<struct sockaddr_in6*>(&addr);
			addr_in6->sin6_family = local_address.ip.family;
			addr_in6->sin6_addr = local_address.ip.addr.v6;
			addr_in6->sin6_port = htons(port);
			size = sizeof(sockaddr_in6);
		}
		if (::bind(fd, reinterpret_cast<struct sockaddr*>(&addr), size) < 0) {
			return -2;
		}
		return 0;
	}

	inline void
	accept(TCP_Connection* conn)
	{
		struct sockaddr_storage remote;
		socklen_t remote_addr_size = sizeof(remote);
		int newfd = ::accept(fd, reinterpret_cast<struct sockaddr*>(&remote), &remote_addr_size);
		if (newfd < 0) {
			throw std::runtime_error("failed to accept connection");
		}
		SockAddr remote_address(remote);
		*conn = std::move(TCP_Connection(newfd, local_address, remote_address));
	}
}; // TCP_Socket

} // net
} // cpl
