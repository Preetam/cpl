#include <tcp_socket.hpp>
#include <cassert>
#include <string>

int
test_tcp_socket() {
	try {
		auto tcp_socket = cpl::net::TCP_Socket();

		auto addr = std::string("127.0.0.1");
		tcp_socket.bind(addr, 8080);

		tcp_socket.listen();
	} catch(...) {
		return 1;
	}

	return 0;
}
