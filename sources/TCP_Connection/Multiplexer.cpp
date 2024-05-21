/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multiplexer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:33:46 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/21 01:40:28 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/TCP_Connection.hpp"

int		TCP_Connection::addClient(int & fd, int & index)
{
	int client_fd = -1;
	size_t tracker = 0;
	for (size_t i = 0; i < this->servers[index].sockets.size(); i++)
	{
		tracker = i;
		if (this->servers[index].sockets[i].socket_fd == fd)
		{
			client_fd = accept(this->servers[index].sockets[i].socket_fd,
				(struct sockaddr *)&this->servers[index].sockets[i].address_s,
				&this->servers[index].sockets[i].address_len);
			if (client_fd < 0)
				TCP_Exception::FailedToAcceptConnections();
			break;
		}
	}
	std::cout << CYAN << "- " << "[" << current_time->tm_hour
		<< ":" << current_time->tm_min << ":"
		<< current_time->tm_sec << "] "
		<<  "- Webserv += " << RESET
		<< "[server " << this->servers[index].index
		<< "], new client connected - "
		<< this->servers[index].config.ip()
		<< std::endl;
	FD_SET(client_fd, &this->fds.current_read_fds);
	this->clients[client_fd].setClientFd(client_fd);
	this->clients[client_fd].config = this->servers[index].config;
	std::pair<int, Client> pair(client_fd, Client(client_fd));
	this->clients[client_fd].setServerFd(this->servers[index].sockets[tracker].socket_fd);
	this->clients[client_fd].setServerIndex(index);
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
		std::cout << GREEN << "- " << "[" << current_time->tm_hour
			<< ":" << current_time->tm_min << ":"
			<< current_time->tm_sec << "] "
			<< "- Webserv >> " << RESET
			<< "[server " << this->clients[fd].getServerIndex()
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
		clients[fd].respons.sendRespons(clients[fd], this->clients[fd].config);
		this->clients[fd].responseContent = clients[fd].respons.getResponsContent();
	}
	bool b = this->clients[fd].writeResponse();
	if (!b)
	{
		std::cout << YELLOW << "- " << "[" << current_time->tm_hour
			<< ":" << current_time->tm_min << ":"
			<< current_time->tm_sec << "] "
			<< "- Webserv << " << RESET
			<< "[server " << this->clients[fd].getServerIndex()
			<< "], response sent Successfully." << std::endl;
		FD_CLR(fd, &this->fds.current_write_fds);
		std::cout << RED << "- " << "[" << current_time->tm_hour
			<< ":" << current_time->tm_min << ":"
			<< current_time->tm_sec << "] "
			<<  "- Webserv -= " << RESET
			<< "[server " << this->clients[fd].getServerIndex()
			<< "], client disconnected." << std::endl;
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
		this->ignoreSIGPIPE(SIGPIPE);
		this->fds.ready_read_fds = this->fds.current_read_fds;
		this->fds.ready_write_fds = this->fds.current_write_fds;

		gettimeofday(&this->log_time, NULL);
		this->current_time = localtime(&this->log_time.tv_sec);

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
					for (size_t j = 0; j < it->second.sockets.size(); j++)
					{
						if (i == it->second.sockets[j].socket_fd)
						{
							int index = it->first;
							if (this->addClient(i, index))
								break;
						}
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
