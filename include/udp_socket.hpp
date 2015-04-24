#ifndef udp_socket_hpp_
#define udp_socket_hpp_

#include <socket.hpp>
#include <sockaddr.hpp>

#include <cstring>

namespace cpl
{
namespace net
{

class UDP_Socket : public Socket
{
public:
	int recvfrom(void* buf, size_t len, int flags, SockAddr* sockaddr)
	{
		struct sockaddr source;
		socklen_t addrlen;

		// Avoid Valgrind errors.
		memset(&source, 0, sizeof source);
		memset(&addrlen, 0, sizeof addrlen);

		auto ret = (int)(::recvfrom(fd, buf, len, flags, &source, &addrlen));
		if (ret < 0) {
			return ret;
		}

		*sockaddr = SockAddr(source);

		return ret;
	}

private:
	
}; // UDP_Socket

} // net
} // cpl

#endif
