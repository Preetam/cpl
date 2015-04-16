#include <ip.hpp>
#include <cassert>

int
test_ip() {

	// IPv4
	auto ip = cpl::net::IP("127.0.0.1");
	assert(ip.string() == "127.0.0.1");

	// IPv6
	ip = cpl::net::IP("dead:beef:cafe:0000:b4d:c0de:0000:0000");
	assert(ip.string() == "dead:beef:cafe:0:b4d:c0de::");

	return 0;
}
