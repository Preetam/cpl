#ifndef udp_socket_hpp_
#define udp_socket_hpp_

#include <socket.hpp>
#include <sockaddr.hpp>

// memset
#include <cstring>

namespace cpl
{
namespace net
{

class UDP_Socket : public Socket
{
public:
	int recvfrom(void* buf, size_t len, int flags, SockAddr* addr)
	{
		struct sockaddr_storage source;
		socklen_t source_len = sizeof source;

		memset(&source, 0, source_len);

		auto ret = (int)(::recvfrom(fd, buf, len, flags, (struct sockaddr*)&source, &source_len));
		if (ret < 0) {
			return ret;
		}

		addr->set(source);

		return ret;
	}

	int sendto(const void* buf, size_t len, int flags, IP address, int port)
	{
		struct sockaddr_storage dest;
		socklen_t dest_len = sizeof dest;

		memset(&dest, 0, dest_len);

		if (address.family() == AF_INET) {
			auto dest_in = reinterpret_cast<struct sockaddr_in*>(&dest);
			dest_in->sin_family = AF_INET;
			dest_in->sin_port = htons((unsigned short)port);
			dest_in->sin_addr = address.addr.v4_addr;
		} else {
			auto dest_in6 = reinterpret_cast<struct sockaddr_in6*>(&dest);
			dest_in6->sin6_family = AF_INET6;
			dest_in6->sin6_port = htons((unsigned short)port);
			dest_in6->sin6_addr = address.addr.v6_addr;
		}

		auto ret = (int)(::sendto(fd, buf, len, flags, reinterpret_cast<struct sockaddr*>(&dest), dest_len));

		return ret;
	}

private:
	
}; // UDP_Socket

} // net
} // cpl

#endif
