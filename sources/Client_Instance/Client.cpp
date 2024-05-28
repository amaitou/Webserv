
#include "../../includes/Client_Instance.hpp"

Client::Client(void)
{
	this->client_fd = -1;
	this->server_fd = -1;
}

Client::Client(int & fd)
{
	this->client_fd = fd;
}

void	Client::setClientFd(int fd)
{
	this->client_fd = fd;
	this->setClientNonBlocking();
}

void	Client::setServerFd(int fd)
{
	this->server_fd = fd;
}

void	Client::setServerIndex(int index)
{
	this->server_index = index;
}

int	Client::getClientFd(void) const
{
	return (this->client_fd);
}

int Client::getServerFd(void) const
{
	return (this->server_fd);
}

int Client::getServerIndex(void) const
{
	return (this->server_index);
}

void Client::setClientNonBlocking(void)
{
	int flags = fcntl(this->getClientFd(), F_GETFL, 0);
	if (flags == -1)
		throw TCP_Exception::FailedToSetNonBlocking();
	if (fcntl(this->getClientFd(), F_SETFL, flags | O_NONBLOCK) == -1)
		throw TCP_Exception::FailedToSetNonBlocking();
}

bool Client::writeResponse(void)
{
	std::string s = this->responseContent.substr(0, 1024);
	this->responseContent = this->responseContent.erase(0, s.length());
	write(this->getClientFd(), s.c_str(), s.length());
	if (this->responseContent.length() == 0)
		return (false);
	return (true);
}

void	Client::setPort(int port)
{
	this->port = port;
}

int	Client::getPort(void) const
{
	return (this->port);
}

void	Client::setIp(std::string ip)
{
	this->ip = ip;
}

std::string	Client::getIp(void) const
{
	return (this->ip);
}