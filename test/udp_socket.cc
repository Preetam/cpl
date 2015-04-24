#include <udp_socket.hpp>
#include <cassert>
#include <string>

int
test_udp_socket() {
	try {
		auto udp_socket = cpl::net::UDP_Socket();

		auto addr = std::string("127.0.0.1");
		udp_socket.bind(addr, 8080);
	} catch(...) {
		return 1;
	}

	return 0;
}
