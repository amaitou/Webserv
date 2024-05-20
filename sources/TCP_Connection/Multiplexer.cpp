/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multiplexer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-amin <ael-amin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:33:46 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/20 14:18:05 by ael-amin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/TCP_Connection.hpp"

int		TCP_Connection::addClient(int & fd)
{
	int client_fd = accept(this->servers[fd].getSocketFd(),
		(struct sockaddr *)&this->servers[fd].address_s,
		&this->servers[fd].address_len);
	if (client_fd < 0)
		return (1);
	std::cout << CYAN << "- [+] Webserv += " << RESET
			<< "[server " << this->servers[fd].index
			<< "], new client connected - "
			<< this->servers[fd].config.ip()
			<< ":" << this->servers[fd].config.listen()[0]
			<< std::endl;
	FD_SET(client_fd, &this->fds.current_read_fds);
	this->clients[client_fd].setClientFd(client_fd);
	std::pair<int, Client> pair(client_fd, Client(client_fd));
	this->clients[client_fd].setServerFd(this->servers[fd].getSocketFd());
	this->clients[client_fd].setServerIndex(this->servers[fd].index);
	this->clients.insert(pair);
	return (0);
}

void	TCP_Connection::readClient(int & fd)
{
	memset(this->buffer, 0, BUFFER_SIZE);
	int r = read(fd, this->buffer, BUFFER_SIZE);
	this->buffer[r] = '\0';
	int v = this->clients[fd].request.addContent(this->buffer, r);
	if (!v)
	{
		this->clients[fd].request.parseRequest();
		std::cout << GREEN << "- [>] Webserv >> " << RESET << "[server " << this->clients[fd].getServerIndex()
			<< "], request received Successfully, [method <"
			<< this->clients[fd].request.stringifyMethod()
			<< ">], [target <" << this->clients[fd].request.getPath()
			<< ">]." << RESET << std::endl;
		FD_CLR(fd, &this->fds.current_read_fds);
		FD_SET(fd, &this->fds.current_write_fds);
	}
}

void	TCP_Connection::writeClient(int & fd)
{
	if (clients[fd].responseContent.length() == 0)
	{
		clients[fd].respons.sendRespons(clients[fd], servers[clients[fd].getServerFd()].config);
		this->clients[fd].responseContent = clients[fd].respons.getResponsContent();
	}
	bool b = this->clients[fd].writeResponse();
	if (!b)
	{
		std::cout << YELLOW << "- [<] Webserv << " << RESET << "[server " << this->clients[fd].getServerIndex() << "], response sent Successfully." << std::endl;
		FD_CLR(fd, &this->fds.current_write_fds);
		std::cout << RED << "- [-] Webserv -= " << RESET << "[server " << this->clients[fd].getServerIndex() << "], client disconnected." << std::endl;
		this->clients.erase(fd);
		close(fd);
	}
	memset(this->buffer, 0, BUFFER_SIZE);
}

void	TCP_Connection::serversMonitoring(void)
{
	std::cout << GREY << "[^] " << RESET << "Monitoring servers :\n" << std::endl;
	while (true)
    {
		this->ignoreSignPipe(SIGPIPE);
		this->fds.ready_read_fds = this->fds.current_read_fds;
		this->fds.ready_write_fds = this->fds.current_write_fds;

		if (select(FD_SETSIZE, &this->fds.ready_read_fds,
			&this->fds.ready_write_fds, NULL, NULL) < 0)
			std::cout << "Failed to select" << std::endl;
		for (int i = 0; i < FD_SETSIZE; ++i)
		{
			if (FD_ISSET(i, &this->fds.ready_read_fds))
			{
				for (std::map<int, Server>::iterator it = this->servers.begin();
					it != this->servers.end(); ++it)
				{
					if (i == it->second.getSocketFd())
					{
						if (this->addClient(i))
							std::cout << "Failed to add client" << std::endl;
						break;
					}
				}
				if (this->clients.find(i) != this->clients.end())
					this->readClient(i);

			}
			else if (FD_ISSET(i, &this->fds.ready_write_fds))
				this->writeClient(i);
		}
    }
}
