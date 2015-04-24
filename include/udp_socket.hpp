#ifndef udp_socket_hpp_
#define udp_socket_hpp_

#include <socket.hpp>
#include <sockaddr.hpp>

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

		auto ret = (int)(::recvfrom(fd, buf, len, flags, (struct sockaddr*)&source, &source_len));
		if (ret < 0) {
			return ret;
		}

		if (local_address.family() == AF_INET) {
			IPv4SockAddr saddr(reinterpret_cast<struct sockaddr&>(source));
			*addr = saddr;
		} else {
			IPv6SockAddr saddr(reinterpret_cast<struct sockaddr&>(source));
			*addr = saddr;
		}

		return ret;
	}

private:
	
}; // UDP_Socket

} // net
} // cpl

#endif
