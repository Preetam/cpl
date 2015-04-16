#ifndef ip_hpp_
#define ip_hpp_

#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <stdexcept>

namespace cpl
{
namespace net
{

class IP
{
public:
	IP(const std::string& address)
	{
		auto s = inet_pton(AF_INET, address.c_str(), &addr.v4_addr);
		if (s == 1) {
			// success
			family = AF_INET;
			return;
		}

		s = inet_pton(AF_INET6, address.c_str(), &addr.v6_addr);
		if (s == 1) {
			// success
			family = AF_INET6;
			return;
		}
		
		throw std::invalid_argument("invalid address");
	}

	~IP() throw()
	{
	}

	std::string string() const
	{
		if (family == AF_INET) {
			// v4
			char str[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, (void*)(&addr), str, INET_ADDRSTRLEN);
			return std::string(str);
		}

		if (family == AF_INET6) {
			// v6
			char str[INET6_ADDRSTRLEN];
			inet_ntop(AF_INET6, (void*)(&addr), str, INET6_ADDRSTRLEN);
			return std::string(str);
		}

		return "";
	}

private:
	int family;
	union {
		in_addr v4_addr;
		in6_addr v6_addr;
	} addr;

	friend std::ostream& operator << (std::ostream& os, const IP& ip);
}; // IP

inline std::ostream& operator << (std::ostream& os, const IP& ip) {
	os << ip.string();
	return os;
}

} // net
} // cpl

#endif
