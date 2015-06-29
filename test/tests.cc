#include <iostream>

#include "tests.hpp"

int
main() {
	int total = 0;
	int passed = 0;
	int failed = 0;

	std::cout << "starting tests" << std::endl;

	if (test_ip()) {
		std::cout << " ✗ test_ip: failed" << std::endl;
		failed++;
	} else {
		std::cout << " ✓ test_ip: passed" << std::endl;
		passed++;
	}
	total++;

	if (test_tcp_socket()) {
		std::cout << " ✗ test_tcp_socket: failed" << std::endl;
		failed++;
	} else {
		std::cout << " ✓ test_tcp_socket: passed" << std::endl;
		passed++;
	}
	total++;


	if (test_udp_socket()) {
		std::cout << " ✗ test_udp_socket: failed" << std::endl;
		failed++;
	} else {
		std::cout << " ✓ test_udp_socket: passed" << std::endl;
		passed++;
	}
	total++;

	std::cout << "finished tests" << std::endl;
	std::cout << std::endl << total << " total tests; " <<
		passed << " passed; " << failed << " failed" << std::endl;

	if (failed > 0) {
		return 1;
	}
}
