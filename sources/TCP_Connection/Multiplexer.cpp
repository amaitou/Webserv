/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multiplexer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:33:46 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/10 16:23:09 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/TCP_Connection.hpp"

void	TCP_Connection::setMultiplexer(void)
{
	FD_ZERO(&this->fds.current_read_fds);
	FD_ZERO(&this->fds.current_write_fds);
	FD_SET(server_fd, &this->fds.current_read_fds);
	FD_SET(server_fd, &this->fds.current_write_fds);
}

int		TCP_Connection::addClient(void)
{
	std::cout << GREY << "[+] New Client Has Connected To The Server" << RESET << std::endl;
	this->client_fd = accept(this->getServerFd(), (struct sockaddr *)&address_s, &address_len);
	if (this->client_fd < 0)
		return (1);
	FD_SET(this->client_fd, &this->fds.current_read_fds);
	clients[client_fd] = Client(client_fd);
	return (0);
}

void	TCP_Connection::readClient(int fd)
{
	memset(buffer, 0, BUFFER_SIZE);
	int r = read(fd, buffer, BUFFER_SIZE);
	buffer[r] = '\0';
	int v = this->clients[fd].request.addContent(buffer, r);
	if (!v)
	{
		clients[fd].request.parseRequest();
		std::cout << ">> Request Has Been Received, " << "Method=<" <<  this->clients[fd].request.stringifyMethod()
			<< ">, " << "Target=<" << this->clients[fd].request.getPath() << ">" << std::endl;
		FD_CLR(fd, &this->fds.current_read_fds);
		FD_SET(fd, &this->fds.current_write_fds);
	}
}

void	TCP_Connection::writeClient(int fd)
{
	std::string p = "<h1>Response Has Been Sent Successfully</h1>";
    std::string http_res = "HTTP/1.1 200 OK Content-Type: text/html\nContent-Length:" + std::to_string(p.length()) + "\n\n" + p + "\n";
	write(fd, http_res.c_str(), http_res.length());
	std::cout << ">> Responded" << std::endl;
	memset(buffer, 0, BUFFER_SIZE);
	FD_CLR(fd, &this->fds.current_write_fds);
	close(fd);
}