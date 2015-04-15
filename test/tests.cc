#include <iostream>

#include "tests.hpp"

int
main() {
	std::cout << "starting tests" << std::endl;

	if (test_ip()) {
		std::cout << "test_ip: failed" << std::endl;
	} else {
		std::cout << "test_ip: passed" << std::endl;
	}

	std::cout << "finished tests" << std::endl;
}