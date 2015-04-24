#ifndef sockaddr_hpp_
#define sockaddr_hpp_

#include <ip.hpp>

#include <stdexcept>

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

	SockAddr(struct sockaddr_storage& addr)
	{
		SockAddr(reinterpret_cast<struct sockaddr&>(addr));
	}

	SockAddr(struct sockaddr& addr)
	{
		family = addr.sa_family;
		if (family == AF_INET) {
			auto addr_in = reinterpret_cast<struct sockaddr_in*>(&addr);
			local_port = addr_in->sin_port;
			local_address = IP(addr_in->sin_addr);
		} else {
			auto addr_in6 = reinterpret_cast<struct sockaddr_in6*>(&addr);
			local_port = addr_in6->sin6_port;
			local_address = IP(addr_in6->sin6_addr);
		}
	}

	~SockAddr() throw()
	{
	}

	IP address() {
		return local_address;
	}

	int port() {
		return local_port;
	}

protected:
	int family;
	IP local_address;
	int local_port;
	
}; // SockAddr

class IPv4SockAddr : public SockAddr
{
public:
	IPv4SockAddr(struct sockaddr& addr)
	: SockAddr(addr)
	{
		if (family != AF_INET) {
			throw std::invalid_argument("invalid address family");
		}
	}

	~IPv4SockAddr() throw()
	{
	}

}; // IPv4SockAddr

class IPv6SockAddr : public SockAddr
{
public:
	IPv6SockAddr(struct sockaddr& addr)
	: SockAddr(addr)
	{
		if (family != AF_INET6) {
			throw std::invalid_argument("invalid address family");
		}

		auto addr_in6 = reinterpret_cast<struct sockaddr_in6*>(&addr);
		flow_info = (int)addr_in6->sin6_flowinfo;
		scope_id = (int)addr_in6->sin6_scope_id;
	}

	~IPv6SockAddr() throw()
	{
	}

private:
	int flow_info;
	int scope_id;
	
}; // IPv6SockAddr

} // net
} // cpl

#endif
