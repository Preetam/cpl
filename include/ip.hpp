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
		if (s < 0) {
			throw std::invalid_argument("invalid address");
		}
	}

	~IP() throw()
	{
	}

private:
	int family;
	union {
		in_addr v4_addr;
		in6_addr v6_addr;
	} addr;

	friend std::ostream& operator << (std::ostream& os, const IP& ip);
};

inline std::ostream& operator<<(std::ostream& os, const IP& ip) {
	char str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, (void*)(&ip.addr), str, INET_ADDRSTRLEN);
	os << str;
	return os;
}

}
}

#endif
