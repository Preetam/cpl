#include <iostream>

#include "tests.hpp"

int
main() {
	std::cout << "starting tests" << std::endl;

	if (test_address()) {
		std::cout << " ✗ test_address: failed" << std::endl;
	} else {
		std::cout << " ✓ test_address: passed" << std::endl;
	}

	if (test_ip()) {
		std::cout << " ✗ test_ip: failed" << std::endl;
	} else {
		std::cout << " ✓ test_ip: passed" << std::endl;
	}

	if (test_tcp_socket()) {
		std::cout << " ✗ test_tcp_socket: failed" << std::endl;
	} else {
		std::cout << " ✓ test_tcp_socket: passed" << std::endl;
	}


	if (test_udp_socket()) {
		std::cout << " ✗ test_udp_socket: failed" << std::endl;
	} else {
		std::cout << " ✓ test_udp_socket: passed" << std::endl;
	}

	std::cout << "finished tests" << std::endl;
}
