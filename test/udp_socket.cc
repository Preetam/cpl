#include <udp_socket.hpp>
#include <sockaddr.hpp>
#include <cassert>
#include <string>

#include <iostream>

int
test_udp_socket() {
	try {
		auto udp_socket = cpl::net::UDP_Socket();

		auto addr = std::string("127.0.0.1");
		udp_socket.bind(addr, 8080);

		// cpl::net::SockAddr saddr;
		// char buf[1000];
		// udp_socket.recvfrom(buf, 1000, 0, &saddr);
		// std::cout << saddr.address() << ":" << saddr.port() << std::endl;
	} catch(...) {
		return 1;
	}

	return 0;
}
