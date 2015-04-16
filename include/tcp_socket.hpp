#ifndef tcp_socket_hpp_
#define tcp_socket_hpp_

#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <stdexcept>

namespace cpl
{
namespace net
{

class TCP_Socket
{
public:
	TCP_Socket()
	{
	}

	~TCP_Socket() throw ()
	{
	}
	
}; // TCP_Socket

} // net
} // cpl

#endif
