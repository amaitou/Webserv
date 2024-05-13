/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multiplexer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:33:46 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/13 17:53:37 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/TCP_Connection.hpp"

int		TCP_Connection::addClient(int fd)
{
	int client_fd = accept(this->servers[fd].server_fd,
		(struct sockaddr *)&this->servers[fd].address_s,
		&this->servers[fd].address_len);
	if (client_fd < 0)
		return (1);
	std::cout << CYAN << "[+] Server += " << RESET
		<< "new client connected to server ["
		<< this->servers[fd].index << "]" << std::endl;
	FD_SET(client_fd, &this->fds.current_read_fds);
	std::pair<int, Client> pair(client_fd, Client(client_fd));
	this->servers[fd].clients.insert(pair);
	return (0);
}

void	TCP_Connection::readClient(int fd)
{
	memset(this->buffer, 0, BUFFER_SIZE);
	int r = read(fd, this->buffer, BUFFER_SIZE);
	this->buffer[r] = '\0';
	int v = this->servers[fd].clients[fd].request.addContent(this->buffer, r);
	if (!v)
	{
		this->servers[fd].clients[fd].request.parseRequest();
		std::cout << GREEN << "[+] Webserv << " << RESET
			<< "request received, [method <"
			<< this->servers[fd].clients[fd].request.stringifyMethod()
			<< ">], [target <" << this->servers[fd].clients[fd].request.getPath()
			<< ">]" << std::endl;
		FD_CLR(fd, &this->fds.current_read_fds);
		FD_SET(fd, &this->fds.current_write_fds);
	}
}

void	TCP_Connection::writeClient(int fd)
{
	std::string p = "<h1>Response Has Been Sent Successfully</h1>";
	std::string http_res = "HTTP/1.1 200 OK Content-Type: text/html\nContent-Length:"
		+ std::to_string(p.length()) + "\n\n" + p + "\n";
	write(fd, http_res.c_str(), http_res.length());
	memset(this->buffer, 0, BUFFER_SIZE);
	std::cout << RED << "[-] Server -= " << RESET
		<< "client disconnected from server" << std::endl;
	FD_CLR(fd, &this->fds.current_write_fds);
	this->servers[fd].clients.erase(fd);
	close(fd);
}

void	TCP_Connection::serversMonitoring(void)
{
	while (true)
    {
		this->fds.ready_read_fds = this->fds.current_read_fds;
		this->fds.ready_write_fds = this->fds.current_write_fds;

		if (select(FD_SETSIZE, &this->fds.ready_read_fds,
			&this->fds.ready_write_fds, NULL, NULL) < 0)
		{
			std::cout << "Failed to select" << std::endl;
		}
		for (int i = 0; i < FD_SETSIZE; ++i)
		{
			if (FD_ISSET(i, &this->fds.ready_read_fds))
			{
				if (i == this->servers[i].server_fd)
				{
					if (this->addClient(i))
						std::cout << "Failed to add client" << std::endl;
				}
				else
					this->readClient(i);
					
			}
			else if (FD_ISSET(i, &this->fds.ready_write_fds))
				this->writeClient(i);
		}
    }
}