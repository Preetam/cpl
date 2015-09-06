#include <tcp_socket.hpp>
#include <cassert>
#include <cstring>
#include <string>

int
test_tcp_socket() {
	cpl::net::TCP_Socket tcp_socket;
	auto addr = std::string("127.0.0.1");
	auto ret = tcp_socket.bind(addr, 8080);
	if (ret < 0) {
		return ret;
	}
	ret = tcp_socket.listen();
	if (ret < 0) {
		return ret;
	}
	return 0;
}
