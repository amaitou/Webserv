
#ifndef SERVER_INSTANCE_HPP
#define SERVER_INSTANCE_HPP

#include "Config.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Buffer Size for reading from socket
#ifndef BUFFER_SIZE
	#define BUFFER_SIZE 1024
#endif

// Typedefs for readability
typedef unsigned long t_ul;
typedef struct sockaddr _sockaddr;
typedef struct sockaddr_in _sockaddr_in;

typedef struct s_socket
{
	_sockaddr_in				address_s;
	socklen_t					address_len;
	int							socket_fd;
	int							port;
} t_socket;

class Server
{
	private:

	public:
		Server(void);
		void	setSocketsNonBlocking(void);
		

		std::vector<t_socket>		sockets;
		int							index;
		Config						config;
};

#endif