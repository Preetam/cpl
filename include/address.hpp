#pragma once

#include <stdexcept>
#include <cstdlib>

#include "ip.hpp"

namespace cpl
{
namespace net
{

struct Address
{
	Address(IP ip, int port)
	: ip(ip), port(port)
	{
	}

	Address(std::string str)
	{
		std::size_t pos = str.rfind(":");
		if (pos == std::string::npos) {
			throw std::invalid_argument("invalid address");
		}

		auto addr_str = str.substr(0, pos);
		auto port_str = str.substr(pos+1);

		if (addr_str[0] == '[' && addr_str[addr_str.size() - 1] == ']') {
			addr_str = addr_str.substr(1, addr_str.size() - 2);
		}

		ip = IP(addr_str);
		port = atoi(port_str.c_str());
	}

	IP ip;
	int port;
};

} // net
} // cpl
