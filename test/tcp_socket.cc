#include <tcp_socket.hpp>
#include <cassert>
#include <cstring>
#include <string>

int
test_tcp_socket() {
	try {
		cpl::net::TCP_Socket tcp_socket;

		auto addr = std::string("127.0.0.1");
		tcp_socket.bind(addr, 8080);

		tcp_socket.listen();

		//auto conn = tcp_socket.accept();
		//const char* message = "hello!\n";
		//conn.send(message, strlen(message), 0);
	} catch(...) {
		return 1;
	}

	return 0;
}
