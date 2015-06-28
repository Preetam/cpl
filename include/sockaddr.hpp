#pragma once

#include "ip.hpp"

namespace cpl
{
namespace net
{

class SockAddr
{
public:
	SockAddr()
	{
	}

	SockAddr(IP ip, int port)
	: address_family(ip.family()), local_address(ip), local_port(port)
	{
	}

	SockAddr(struct sockaddr_storage& addr)
	{
		set(reinterpret_cast<struct sockaddr&>(addr));
	}

	SockAddr(struct sockaddr& addr)
	{
		set(addr);
	}

	inline void set(struct sockaddr& addr)
	{
		address_family = addr.sa_family;
		if (address_family == AF_INET) {
			auto addr_in = reinterpret_cast<struct sockaddr_in*>(&addr);
			local_port = ntohs(addr_in->sin_port);
			local_address = IP(addr_in->sin_addr);
		} else {
			auto addr_in6 = reinterpret_cast<struct sockaddr_in6*>(&addr);
			local_port = ntohs(addr_in6->sin6_port);
			local_address = IP(addr_in6->sin6_addr);
		}
	}

	inline void set(struct sockaddr_storage& addr)
	{
		set(reinterpret_cast<struct sockaddr&>(addr));
	}

	inline int family() {
		return address_family;
	}

	inline IP address() {
		return local_address;
	}

	inline int port() {
		return local_port;
	}

protected:
	int address_family;
	IP local_address;
	int local_port;
	
}; // SockAddr

} // net
} // cpl
