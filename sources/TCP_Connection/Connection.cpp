/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:02:08 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/21 01:40:21 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/TCP_Connection.hpp"

TCP_Connection::TCP_Connection(std::vector<Config> &config)
{
	this->displayBanner();
	std::cout << GREY << "[.] " << RESET << "Creating servers..."
		<< std::endl;
	for (size_t i = 0; i < config.size(); i++)
	{
		Server server;
		server.config = config[i];
		server.index = i + 1;
		std::vector<t_socket> sockets;
		for (size_t j = 0; j < config[i].listen().size(); j++)
		{
			t_socket _socket;
			memset(&_socket.address_s, 0, sizeof(_socket.address_s));
			_socket.address_s.sin_family = AF_INET;
			_socket.address_s.sin_port = htons(config[i].listen()[j]);
			_socket.address_s.sin_addr.s_addr = htonl(INADDR_ANY);
			_socket.address_len = sizeof(_socket.address_s);
			_socket.socket_fd = socket(_socket.address_s.sin_family, SOCK_STREAM, 0);
			if (_socket.socket_fd < 0)
				throw TCP_Exception::FailedToCreateSocket();
			sockets.push_back(_socket);
		}
		memset(this->buffer, 0, BUFFER_SIZE);
		server.index = i + 1;
		server.sockets = sockets;
		server.setSocketsNonBlocking();
		std::pair<int, Server> pair = std::make_pair(i + 1, server);
		this->servers.insert(pair);
	}
	FD_ZERO(&this->fds.current_read_fds);
	FD_ZERO(&this->fds.current_write_fds);
	for (std::map<int, Server>::iterator it = this->servers.begin();
		it != this->servers.end(); it++)
	{
		for (size_t i = 0; i < it->second.sockets.size(); i++)
		{
			FD_SET(it->second.sockets[i].socket_fd, &this->fds.current_read_fds);
			FD_SET(it->second.sockets[i].socket_fd, &this->fds.current_write_fds);
		}
	}
	std::cout << YELLOW << "[+] " << RESET << "Servers were created." << std::endl;
}

void TCP_Connection::socketAccept(void)
{
    this->serversMonitoring();
}

void TCP_Connection::serve(void)
{
	setSocketOptions();
	socketBind();
	socketListen();
	socketAccept();
}

void TCP_Connection::ignoreSIGPIPE(int _signal)
{
	std::signal(_signal, SIG_IGN);
}
