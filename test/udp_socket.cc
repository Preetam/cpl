#include <udp_socket.hpp>
#include <sockaddr.hpp>
#include <cassert>
#include <string>

#include <iostream>

int
test_udp_socket() {
	cpl::net::UDP_Socket udp_socket;
	auto addr = std::string("127.0.0.1");
	auto ret = udp_socket.bind(addr, 8080);
	if (ret < 0) {
		return ret;
	}
	return 0;
}
