#pragma once

#include <sstream> // osstringstream
#include <iostream> // ostream
#include <cstdlib> // atoi
#include <stdexcept> // std::invalid_argument

#include "ip.hpp"

namespace cpl
{
namespace net
{

struct SockAddr
{
	IP ip;
	int port;

	SockAddr()
	{
	}

	SockAddr(IP ip, int port)
	: ip(ip), port(port)
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

	inline int
	parse(std::string str)
	{
		std::size_t pos = str.rfind(":");
		if (pos == std::string::npos) {
			return -1;
		}
		auto addr_str = str.substr(0, pos);
		auto port_str = str.substr(pos+1);

		if (addr_str[0] == '[' && addr_str[addr_str.size() - 1] == ']') {
			addr_str = addr_str.substr(1, addr_str.size() - 2);
		}

		if (ip.set(addr_str) < 0) {
			return -1;
		}
		port = atoi(port_str.c_str());
		return 0;
	}

	inline void
	set(struct sockaddr& addr)
	{
		auto address_family = addr.sa_family;
		if (address_family == AF_INET) {
			auto addr_in = reinterpret_cast<struct sockaddr_in*>(&addr);
			port = ntohs(addr_in->sin_port);
			ip = IP(addr_in->sin_addr);
		} else {
			auto addr_in6 = reinterpret_cast<struct sockaddr_in6*>(&addr);
			port = ntohs(addr_in6->sin6_port);
			ip = IP(addr_in6->sin6_addr);
		}
	}

	inline void
	set(struct sockaddr_storage& addr)
	{
		set(reinterpret_cast<struct sockaddr&>(addr));
	}

	inline void
	get_sockaddr(struct sockaddr* sockaddr)
	{
		sockaddr->sa_family = ip.family;
		if (ip.family == AF_INET) {
			auto addr_in = reinterpret_cast<struct sockaddr_in*>(sockaddr);
			addr_in->sin_port = htons(port);
			addr_in->sin_addr = ip.addr.v4;
		} else {
			auto addr_in6 = reinterpret_cast<struct sockaddr_in6*>(sockaddr);
			addr_in6->sin6_port = htons(port);
			addr_in6->sin6_addr = ip.addr.v6;
		}
	}

	friend std::ostream& operator << (std::ostream& os, const SockAddr& address)
	{
		os << address.ip << ":" << address.port;
		return os;
	}

	std::string
	str() const
	{
		std::string s;
		std::ostringstream os;
		os << ip << ":" << port;
		s = os.str();
		return s;
	}
}; // SockAddr

} // net
} // cpl
