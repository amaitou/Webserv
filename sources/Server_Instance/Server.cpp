
#include "../../includes/Server_Instance.hpp"
#include "../../includes/TCP_Exceptions.hpp"
#include <fcntl.h>

Server::Server(void) {}

void Server::setSocketsNonBlocking(void)
{
	for (size_t i = 0; i < this->sockets.size(); i++)
	{
		if (fcntl(this->sockets[i].socket_fd, F_SETFL, O_NONBLOCK) < 0)
			throw TCP_Exception::FailedToSetNonBlocking();
	}
}