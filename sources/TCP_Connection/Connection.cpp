/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:02:08 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/13 17:19:09 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/TCP_Connection.hpp"

TCP_Connection::TCP_Connection(std::vector<Config> &config)
{
	std::cout << GREY << "[.] " << RESET << "Creating servers..."
		<< std::endl;
	for (size_t i = 0; i < config.size(); i++)
	{
		Server server;
		memset(&server.address_s, 0, sizeof(server.address_s));
		memset(this->buffer, 0, BUFFER_SIZE);
		server.address_s.sin_family = AF_INET;
		server.address_s.sin_port = htons(config[i].listen()[0]);
		server.address_s.sin_addr.s_addr = htonl(INADDR_ANY);
		server.address_len = sizeof(server.address_s);
		int socket_fd = socket(server.address_s.sin_family, SOCK_STREAM, 0);
		if (socket_fd < 0)
			throw TCP_Exception::FailedToCreateSocket();
		server.server_fd = socket_fd;
		server.setServerNonBlocking();
		server.index = i + 1;
		std::pair<int, Server> pair(socket_fd, server);
		this->servers.insert(pair);
	}
	FD_ZERO(&this->fds.current_read_fds);
	FD_ZERO(&this->fds.current_write_fds);
	for (std::map<int, Server>::iterator it = this->servers.begin();
		it != this->servers.end(); it++)
	{
		FD_SET(it->first, &this->fds.current_read_fds);
		FD_SET(it->first, &this->fds.current_write_fds);
	}
	std::cout << YELLOW << "[+] " << RESET << "Servers were created." << std::endl;
}

void TCP_Connection::socketAccept(void)
{
    this->serversMonitoring();
}

void TCP_Connection::serve(void)
{
	// setSocketOptions();
	socketBind();
	socketListen();
	socketAccept();
}