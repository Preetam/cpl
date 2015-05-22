#include <address.hpp>
#include <cassert>

int
test_address() {
	try {
		cpl::net::Address addr1("127.0.0.1:2020");
		assert(addr1.port == 2020);
		assert(addr1.ip.string() == "127.0.0.1");
	} catch (...) {
		return 1;
	}

	try {
		cpl::net::Address addr2("[::1]:2020");
		assert(addr2.port == 2020);
		assert(addr2.ip.string() == "::1");
	} catch (...) {
		return 1;
	}

	return 0;
}
